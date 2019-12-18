#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct s_write {int prev_font_style; int prev_font_color; } ;
struct eia608_screen {unsigned char** characters; int** colors; int** fonts; } ;

/* Variables and functions */
 int COL_WHITE ; 
 int FONT_ITALICS ; 
 int FONT_STYLE_MASK ; 
 int FONT_UNDERLINED ; 
 scalar_t__** color_text ; 
 int /*<<< orphan*/  encode_line (unsigned char*,int*) ; 
 int /*<<< orphan*/  find_limit_characters (unsigned char*,int*,int*) ; 
 int get_char_in_utf8 (unsigned char*,unsigned char) ; 

__attribute__((used)) static unsigned get_decoder_line_encoded(struct s_write *wb,
                                         unsigned char *buffer, int line_num,
                                         struct eia608_screen *data)
{
    uint8_t font_style;
    uint8_t font_color;
    int i;

    unsigned char *line = data->characters[line_num];
    unsigned char *orig = buffer; // Keep for debugging
    int first = 0, last = 31;

    find_limit_characters(line, &first, &last);
    for (i = first; i <= last; i++)
    {
        // Handle color
        font_color = data->colors[line_num][i];
        font_style = data->fonts[line_num][i];

        // Handle reset to defaults
        if ((font_style & FONT_STYLE_MASK) == 0 && font_color == COL_WHITE)
        {
            if (((font_style ^ wb->prev_font_style) & FONT_STYLE_MASK) ||
                (font_color != wb->prev_font_color))
            {
                buffer += encode_line(buffer, (uint8_t*)"{\\r}");
            }
        }
        else
        {
            // Open markup
            if (((font_style ^ wb->prev_font_style) & FONT_STYLE_MASK) ||
                (font_color != wb->prev_font_color))
            {
                // style changed
                buffer += encode_line(buffer, (uint8_t*)"{");
            }

            // Handle underlined
            if ((font_style ^ wb->prev_font_style) & FONT_UNDERLINED)
            {
                int enable = !!(font_style & FONT_UNDERLINED);
                buffer += encode_line(buffer, (uint8_t*)"\\u");
                *buffer++ = enable + 0x30;
            }

            // Handle italics
            if ((font_style ^ wb->prev_font_style) & FONT_ITALICS)
            {
                int enable = !!(font_style & FONT_ITALICS);
                buffer += encode_line(buffer, (uint8_t*)"\\i");
                *buffer++ = enable + 0x30;
            }

            // Handle color
            if (font_color != wb->prev_font_color)
            {
                buffer += encode_line(buffer, (uint8_t*)"\\1c");
                buffer += encode_line(buffer,
                                      (uint8_t*)color_text[font_color][1]);
            }

            // Close markup
            if (((font_style ^ wb->prev_font_style) & FONT_STYLE_MASK) ||
                (font_color != wb->prev_font_color))
            {
                // style changed
                buffer += encode_line(buffer, (uint8_t*)"}");
            }
        }
        wb->prev_font_style = font_style;
        wb->prev_font_color = font_color;

        int bytes = 0;
        bytes = get_char_in_utf8(buffer, line[i]);
        buffer += bytes;
    }
    *buffer = 0;
    return (unsigned) (buffer - orig); // Return length
}