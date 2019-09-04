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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int** data; int* linesize; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WL32 (int*,int /*<<< orphan*/ ) ; 
 int* avpriv_cga_font ; 

__attribute__((used)) static void drawtext(AVFrame *pic, int x, int y, const char *txt, uint32_t color)
{
    const uint8_t *font;
    int font_height;
    int i;

    font = avpriv_cga_font, font_height = 8;

    for (i = 0; txt[i]; i++) {
        int char_y, mask;

        uint8_t *p = pic->data[0] + y * pic->linesize[0] + (x + i * 8) * 4;
        for (char_y = 0; char_y < font_height; char_y++) {
            for (mask = 0x80; mask; mask >>= 1) {
                if (font[txt[i] * font_height + char_y] & mask)
                    AV_WL32(p, color);
                p += 4;
            }
            p += pic->linesize[0] - 8 * 4;
        }
    }
}