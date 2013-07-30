#ifndef FONT_H_
#define FONT_H_

#include "SpriteBatch.h"

namespace gameplay
{

/**
 * Defines a font for text rendering.
 */
class Font : public Ref
{
    friend class Bundle;
    friend class TextBox;

public:

    /**
     * Defines the set of allowable font styles.
     */
    enum Style
    {
        PLAIN = 0,
        BOLD = 1,
        ITALIC = 2,
        BOLD_ITALIC = 4,
        TEXTURED = 5,
    };

    /**
     * Defines the set of allowable alignments when drawing text.
     */
    enum Justify
    {
        ALIGN_LEFT = 0x01,
        ALIGN_HCENTER = 0x02,
        ALIGN_RIGHT = 0x04,
        ALIGN_TOP = 0x10,
        ALIGN_VCENTER = 0x20,
        ALIGN_BOTTOM = 0x40,
        ALIGN_TOP_LEFT = ALIGN_TOP | ALIGN_LEFT,
        ALIGN_VCENTER_LEFT = ALIGN_VCENTER | ALIGN_LEFT,
        ALIGN_BOTTOM_LEFT = ALIGN_BOTTOM | ALIGN_LEFT,
        ALIGN_TOP_HCENTER = ALIGN_TOP | ALIGN_HCENTER,
        ALIGN_VCENTER_HCENTER = ALIGN_VCENTER | ALIGN_HCENTER,
        ALIGN_BOTTOM_HCENTER = ALIGN_BOTTOM | ALIGN_HCENTER,
        ALIGN_TOP_RIGHT = ALIGN_TOP | ALIGN_RIGHT,
        ALIGN_VCENTER_RIGHT = ALIGN_VCENTER | ALIGN_RIGHT,
        ALIGN_BOTTOM_RIGHT = ALIGN_BOTTOM | ALIGN_RIGHT
    };

    /**
     * Vertex coordinates, UVs and indices can be computed and stored in a Text object.
     * For static text labels that do not change frequently, this means these computations
     * need not be performed every frame.
     */
    class Text
    {
        friend class Font;

    public:
        /**
         * Constructor.
         */
        Text(const char* text);

        /**
         * Destructor.
         */
        ~Text();

        /**
         * Get the string that will be drawn from this Text object.
         */
        const char* getText();

    private:
        /**
         * Hidden copy constructor.
         */
        Text(const Text&); 
        /**
         * Hidden copy assignment operator.
         */
        Text& operator=(const Text&);
        
        std::string _text;
        unsigned int _vertexCount;
        SpriteBatch::SpriteVertex* _vertices;
        Vector4 _color;
    };

    /**
     * Creates a font from the given bundle.
     *
     * If the 'id' parameter is NULL, it is assumed that the Bundle at 'path'
     * contains exactly one Font resource. If the Bundle does not meet this criteria,
     * NULL is returned.
     *
     * If a font for the given path has already been loaded, the existing font will be
     * returned with its reference count increased.
     *
     * @param path The path to a bundle file containing a font resource.
     * @param id An optional ID of the font resource within the bundle (NULL for the first/only resource).
     * 
     * @return The specified font.
     * @script{create}
     */
    static Font* create(const char* path, const char* id = NULL);

    /**
     * Returns the font size (max height of glyphs) in pixels.
     */
    unsigned int getSize() const;

    /**
     * Starts text drawing for this font.
     */
    void start() const;

    /**
     * Draws the specified text in a solid color, with a scaling factor.
     *
     * @param text The text to draw.
     * @param x The viewport x position to draw text at.
     * @param y The viewport y position to draw text at.
     * @param color The color of text.
     * @param size The size to draw text (0 for default size).
     * @param rightToLeft Whether to draw text from right to left.
     */
    void drawText(const char* text, float x, float y, const Vector4& color, float size = 0, bool rightToLeft = false) const;

    /**
     * Draws the specified text in a solid color, with a scaling factor.
     * 
     * @param text The text to draw.
     * @param x The viewport x position to draw text at.
     * @param y The viewport y position to draw text at.
     * @param red The red channel of the text color.
     * @param green The green channel of the text color.
     * @param blue The blue channel of the text color.
     * @param alpha The alpha channel of the text color.
     * @param size The size to draw text (0 for default size).
     * @param rightToLeft Whether to draw text from right to left.
     */
    void drawText(const char* text, float x, float y, float red, float green, float blue, float alpha, float size = 0, bool rightToLeft = false) const;

    /**
     * Draws the specified text within a rectangular area, with a specified alignment and scale.
     * Clips text outside the viewport. Optionally wraps text to fit within the width of the viewport.
     *
     * @param text The text to draw.
     * @param area The viewport area to draw within.  Text will be clipped outside this rectangle.
     * @param color The color of text.
     * @param size The size to draw text (0 for default size).
     * @param justify Justification of text within the viewport.
     * @param wrap Wraps text to fit within the width of the viewport if true.
     * @param rightToLeft Whether to draw text from right to left.
     * @param clip A region to clip text within after applying justification to the viewport area.
     */
    void drawText(const char* text, const Rectangle& area, const Vector4& color, float size = 0, 
                  Justify justify = ALIGN_TOP_LEFT, bool wrap = true, bool rightToLeft = false, const Rectangle* clip = NULL) const;

    /**
     * Draw a string from a precomputed Text object.
     *
     * @param text The text to draw.
     */
    void drawText(Text* text) const;

    /**
     * Create an immutable Text object from a given string.
     * Vertex coordinates, UVs and indices will be computed and stored in the Text object.
     * For static text labels that do not change frequently, this means these computations
     * need not be performed every frame.
     *
     * @param text The text to draw.
     * @param area The viewport area to draw within.  Text will be clipped outside this rectangle.
     * @param color The color of text.
     * @param size The size to draw text (0 for default size).
     * @param justify Justification of text within the viewport.
     * @param wrap Wraps text to fit within the width of the viewport if true.
     * @param rightToLeft Whether to draw text from right to left.
     * @param clip A region to clip text within after applying justification to the viewport area.
     *
     * @return A Text object.
     */
    Text* createText(const char* text, const Rectangle& area, const Vector4& color, float size = 0,
                     Justify justify = ALIGN_TOP_LEFT, bool wrap = true, bool rightToLeft = false, const Rectangle* clip = NULL);

    /**
     * Finishes text batching for this font and renders all drawn text.
     */
    void finish() const;

    /**
     * Measures a string's width and height without alignment, wrapping or clipping.
     *
     * @param text The text to measure.
     * @param size The font height to scale to.
     * @param widthOut Destination for the text's width.
     * @param heightOut Destination for the text's height.
     */
    void measureText(const char* text, float size, float* widthOut, float* heightOut) const;

    /**
     * Measures a string's bounding box after alignment, wrapping and clipping within a viewport.
     *
     * @param text The text to measure.
     * @param clip The clip rectangle.
     * @param size The font height to scale to.
     * @param out Destination rectangle to store the bounds in.
     * @param justify Justification of text within the viewport.
     * @param wrap Whether to measure text with wrapping applied.
     * @param ignoreClip Whether to clip 'out' to the viewport.  Set false for the bounds of what would actually be drawn
     *                within the given viewport; true for bounds that are guaranteed to fit the entire string of text.
     */
    void measureText(const char* text, const Rectangle& clip, float size, Rectangle* out,
                     Justify justify = ALIGN_TOP_LEFT, bool wrap = true, bool ignoreClip = false) const;

    /**
     * Returns current character spacing for this font in percentage of fonts size.
     *
     * @see setCharacterSpacing(float)
     */
    float getCharacterSpacing() const;

    /**
     * Sets the fixed character spacing for this font.
     *
     * Character spacing is the fixed amount of space that is inserted between characters. This is a simplified
     * type of kerning and does not take adjacent characters into consideration. Character spacing is defined
     * as a floating point value that is interpreted as a percentage of size used to draw the font. For example,
     * a value of 0.1 would cause a spacing of 10% of the font size to be inserted between adjacent characters.
     * For a font size of 20, this would equate to 2 pixels of extra space between characters.
     *
     * The default character spacing for fonts is 0.125.
     *
     * @param spacing New fixed character spacing, expressed as a percentage of font size.
     */
    void setCharacterSpacing(float spacing);

    /**
     * Get an character index into a string corresponding to the character nearest the given location within the clip region.
     */
    int getIndexAtLocation(const char* text, const Rectangle& clip, float size, const Vector2& inLocation, Vector2* outLocation,
                           Justify justify = ALIGN_TOP_LEFT, bool wrap = true, bool rightToLeft = false) const;

    /**
     * Get the location of the character at the given index.
     */
    void getLocationAtIndex(const char* text, const Rectangle& clip, float size, Vector2* outLocation, const unsigned int destIndex,
                            Justify justify = ALIGN_TOP_LEFT, bool wrap = true, bool rightToLeft = false) const;

    /**
     * Gets the sprite batch for this Font.
     * 
     * @return The sprite batch for this Font.
     */
    SpriteBatch* getSpriteBatch() const;

    /**
     * Gets the Justify value from the given string.
     * Returns ALIGN_TOP_LEFT if the string is unrecognized.
     * 
     * @param justify The string such as "ALIGN_HCENTER" or "ALIGN_VCENTER_RIGHT".
     * 
     * @return The Justify value.
     */
    static Justify getJustify(const char* justify);

public:

    /**
     * Defines a font glyph within the texture map for a font.
     */
    class Glyph
    {
    public:
        /**
         * Glyph character code (decimal value).
         */
        unsigned int code;

        /**
         * Glyph width (in pixels).
         */
        unsigned int width;

        /**
         * Glyph texture coordinates.
         */
        float uvs[4];
    };

    /**
     * Gets glyph by character code or NULL.
     */
    const Glyph * getGlyphByCode( int characterCode ) const;

private:
    /**
     * Constructor.
     */
    Font();

    /**
     * Constructor.
     */
    Font(const Font& copy);

    /**
     * Destructor.
     */
    ~Font();

    /**
     * Hidden copy assignment operator.
     */
    Font& operator=(const Font&);

    /**
     * Creates a font with the given characteristics from the specified glyph array and texture map.
     *
     * This method will create a new Font object regardless of whether another Font is already
     * created with the same attributes.
     *
     * @param family The font family name.
     * @param style The font style.
     * @param size The font size.
     * @param glyphs An array of font glyphs, defining each character in the font within the texture map.
     * @param glyphCount The number of items in the glyph array.
     * @param texture A texture map containing rendered glyphs.
     * 
     * @return The new Font.
     */
    static Font* create(const char* family, Style style, unsigned int size, Glyph* glyphs, int glyphCount, Texture* texture);

    void getMeasurementInfo(const char* text, const Rectangle& area, float size, Justify justify, bool wrap, bool rightToLeft,
                            std::vector<float>* xPositions, float* yPosition, std::vector<unsigned int>* lineLengths) const;

    int getIndexOrLocation(const char* text, const Rectangle& clip, float size, const Vector2& inLocation, Vector2* outLocation,
                           const int destIndex = -1, Justify justify = ALIGN_TOP_LEFT, bool wrap = true, bool rightToLeft = false) const;

    float getTokenWidth(const char* token, unsigned int length, float size, float scale) const;

    unsigned int getReversedTokenLength(const char* token, const char* bufStart) const;

    int handleDelimiters(const char** token, const float size, const int iteration, const float areaX, float* xPos, float* yPos, unsigned int* lineLength,
                         std::vector<float>::const_iterator* xPositionsIt, std::vector<float>::const_iterator xPositionsEnd, unsigned int* charIndex = NULL,
                         const Vector2* stopAtPosition = NULL, const int currentIndex = -1, const int destIndex = -1) const;

    void addLineInfo(const Rectangle& area, float lineWidth, int lineLength, Justify hAlign,
                     std::vector<float>* xPositions, std::vector<unsigned int>* lineLengths, bool rightToLeft) const;

    //! Returns glyph index by character code or -1.
    int getGlyphIndexByCode( int characterCode ) const;

    std::string _path;
    std::string _id;
    std::string _family;
    Style _style;
    unsigned int _size;
    float _spacing;
    Glyph* _glyphs;
    unsigned int _glyphCount;
    Texture* _texture;
    SpriteBatch* _batch;
    Rectangle _viewport;
};

}

#endif
