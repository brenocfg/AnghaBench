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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int av_clip_uintp2 (int,int) ; 
 int** match5 ; 
 int** match6 ; 

__attribute__((used)) static int refine_colors(const uint8_t *block, ptrdiff_t stride,
                         uint16_t *pmax16, uint16_t *pmin16, uint32_t mask)
{
    uint32_t cm = mask;
    uint16_t oldMin = *pmin16;
    uint16_t oldMax = *pmax16;
    uint16_t min16, max16;
    int x, y;

    /* Additional magic to save a lot of multiplies in the accumulating loop.
     * The tables contain precomputed products of weights for least squares
     * system, accumulated inside one 32-bit register */
    static const int w1tab[4] = { 3, 0, 2, 1 };
    static const int prods[4] = { 0x090000, 0x000900, 0x040102, 0x010402 };

    /* Check if all pixels have the same index */
    if ((mask ^ (mask << 2)) < 4) {
        /* If so, linear system would be singular; solve using optimal
         * single-color match on average color. */
        int r = 8, g = 8, b = 8;
        for (y = 0; y < 4; y++) {
            for (x = 0; x < 4; x++) {
                r += block[0 + x * 4 + y * stride];
                g += block[1 + x * 4 + y * stride];
                b += block[2 + x * 4 + y * stride];
            }
        }

        r >>= 4;
        g >>= 4;
        b >>= 4;

        max16 = (match5[r][0] << 11) | (match6[g][0] << 5) | match5[b][0];
        min16 = (match5[r][1] << 11) | (match6[g][1] << 5) | match5[b][1];
    } else {
        float fr, fg, fb;
        int at1_r = 0, at1_g = 0, at1_b = 0;
        int at2_r = 0, at2_g = 0, at2_b = 0;
        int akku = 0;
        int xx, xy, yy;

        for (y = 0; y < 4; y++) {
            for (x = 0; x < 4; x++) {
                int step = cm & 3;
                int w1 = w1tab[step];
                int r = block[0 + x * 4 + y * stride];
                int g = block[1 + x * 4 + y * stride];
                int b = block[2 + x * 4 + y * stride];

                akku  += prods[step];
                at1_r += w1 * r;
                at1_g += w1 * g;
                at1_b += w1 * b;
                at2_r += r;
                at2_g += g;
                at2_b += b;

                cm >>= 2;
            }
        }

        at2_r = 3 * at2_r - at1_r;
        at2_g = 3 * at2_g - at1_g;
        at2_b = 3 * at2_b - at1_b;

        /* Extract solutions and decide solvability */
        xx =  akku >> 16;
        yy = (akku >>  8) & 0xFF;
        xy = (akku >>  0) & 0xFF;

        fr = 3.0f * 31.0f / 255.0f / (xx * yy - xy * xy);
        fg = fr * 63.0f / 31.0f;
        fb = fr;

        /* Solve */
        max16  = av_clip_uintp2((at1_r * yy - at2_r * xy) * fr + 0.5f, 5) << 11;
        max16 |= av_clip_uintp2((at1_g * yy - at2_g * xy) * fg + 0.5f, 6) <<  5;
        max16 |= av_clip_uintp2((at1_b * yy - at2_b * xy) * fb + 0.5f, 5) <<  0;

        min16  = av_clip_uintp2((at2_r * xx - at1_r * xy) * fr + 0.5f, 5) << 11;
        min16 |= av_clip_uintp2((at2_g * xx - at1_g * xy) * fg + 0.5f, 6) <<  5;
        min16 |= av_clip_uintp2((at2_b * xx - at1_b * xy) * fb + 0.5f, 5) <<  0;
    }

    *pmin16 = min16;
    *pmax16 = max16;
    return oldMin != min16 || oldMax != max16;
}