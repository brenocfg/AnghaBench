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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int* png_pass_dsp_mask ; 
 int* png_pass_mask ; 

__attribute__((used)) static void png_put_interlaced_row(uint8_t *dst, int width,
                                   int bits_per_pixel, int pass,
                                   int color_type, const uint8_t *src)
{
    int x, mask, dsp_mask, j, src_x, b, bpp;
    uint8_t *d;
    const uint8_t *s;

    mask     = png_pass_mask[pass];
    dsp_mask = png_pass_dsp_mask[pass];

    switch (bits_per_pixel) {
    case 1:
        src_x = 0;
        for (x = 0; x < width; x++) {
            j = (x & 7);
            if ((dsp_mask << j) & 0x80) {
                b = (src[src_x >> 3] >> (7 - (src_x & 7))) & 1;
                dst[x >> 3] &= 0xFF7F>>j;
                dst[x >> 3] |= b << (7 - j);
            }
            if ((mask << j) & 0x80)
                src_x++;
        }
        break;
    case 2:
        src_x = 0;
        for (x = 0; x < width; x++) {
            int j2 = 2 * (x & 3);
            j = (x & 7);
            if ((dsp_mask << j) & 0x80) {
                b = (src[src_x >> 2] >> (6 - 2*(src_x & 3))) & 3;
                dst[x >> 2] &= 0xFF3F>>j2;
                dst[x >> 2] |= b << (6 - j2);
            }
            if ((mask << j) & 0x80)
                src_x++;
        }
        break;
    case 4:
        src_x = 0;
        for (x = 0; x < width; x++) {
            int j2 = 4*(x&1);
            j = (x & 7);
            if ((dsp_mask << j) & 0x80) {
                b = (src[src_x >> 1] >> (4 - 4*(src_x & 1))) & 15;
                dst[x >> 1] &= 0xFF0F>>j2;
                dst[x >> 1] |= b << (4 - j2);
            }
            if ((mask << j) & 0x80)
                src_x++;
        }
        break;
    default:
        bpp = bits_per_pixel >> 3;
        d   = dst;
        s   = src;
            for (x = 0; x < width; x++) {
                j = x & 7;
                if ((dsp_mask << j) & 0x80) {
                    memcpy(d, s, bpp);
                }
                d += bpp;
                if ((mask << j) & 0x80)
                    s += bpp;
            }
        break;
    }
}