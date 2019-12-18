#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int color ;
struct TYPE_5__ {size_t transparency; TYPE_1__* frame; } ;
struct TYPE_4__ {int palette_has_changed; scalar_t__* data; } ;
typedef  TYPE_2__ CDGraphicsContext ;

/* Variables and functions */

__attribute__((used)) static void cdg_load_palette(CDGraphicsContext *cc, uint8_t *data, int low)
{
    uint8_t r, g, b;
    uint16_t color;
    int i;
    int array_offset  = low ? 0 : 8;
    uint32_t *palette = (uint32_t *) cc->frame->data[1];

    for (i = 0; i < 8; i++) {
        color = (data[2 * i] << 6) + (data[2 * i + 1] & 0x3F);
        r = ((color >> 8) & 0x000F) * 17;
        g = ((color >> 4) & 0x000F) * 17;
        b = ((color     ) & 0x000F) * 17;
        palette[i + array_offset] = 0xFFU << 24 | r << 16 | g << 8 | b;
        if (cc->transparency >= 0)
            palette[cc->transparency] &= 0xFFFFFF;
    }
    cc->frame->palette_has_changed = 1;
}