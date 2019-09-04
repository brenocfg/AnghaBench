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
typedef  float uint16_t ;
struct TYPE_3__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int* avpriv_cga_font ; 

__attribute__((used)) static void draw_vtext16(AVFrame *out, int x, int y, int mult, float o1, float o2, const char *txt, const uint8_t color[4])
{
    const uint8_t *font;
    int font_height;
    int i, plane;

    font = avpriv_cga_font,   font_height =  8;

    for (plane = 0; plane < 4 && out->data[plane]; plane++) {
        for (i = 0; txt[i]; i++) {
            int char_y, mask;
            int v = color[plane] * mult;

            for (char_y = 0; char_y < font_height; char_y++) {
                uint16_t *p = (uint16_t *)(out->data[plane] + (y + i * 10) * out->linesize[plane]) + x;
                for (mask = 0x80; mask; mask >>= 1) {
                    if (font[txt[i] * font_height + font_height - 1 - char_y] & mask)
                        p[char_y] = p[char_y] * o2 + v * o1;
                    p += out->linesize[plane] / 2;
                }
            }
        }
    }
}