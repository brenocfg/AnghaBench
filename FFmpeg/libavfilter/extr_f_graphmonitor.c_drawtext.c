#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int height; int width; int** data; int* linesize; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int* avpriv_cga_font ; 
 int strlen (char const*) ; 

__attribute__((used)) static void drawtext(AVFrame *pic, int x, int y, const char *txt, uint8_t *color)
{
    const uint8_t *font;
    int font_height;
    int i;

    font = avpriv_cga_font,   font_height =  8;

    if (y + 8 >= pic->height ||
        x + strlen(txt) * 8 >= pic->width)
        return;

    for (i = 0; txt[i]; i++) {
        int char_y, mask;

        uint8_t *p = pic->data[0] + y*pic->linesize[0] + (x + i*8)*4;
        for (char_y = 0; char_y < font_height; char_y++) {
            for (mask = 0x80; mask; mask >>= 1) {
                if (font[txt[i] * font_height + char_y] & mask) {
                    p[0] = color[0];
                    p[1] = color[1];
                    p[2] = color[2];
                }
                p += 4;
            }
            p += pic->linesize[0] - 8 * 4;
        }
    }
}