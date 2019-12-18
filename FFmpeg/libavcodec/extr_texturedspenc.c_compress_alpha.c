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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void compress_alpha(uint8_t *dst, ptrdiff_t stride, const uint8_t *block)
{
    int x, y;
    int dist, bias, dist4, dist2;
    int mn, mx;
    int bits = 0;
    int mask = 0;

    memset(dst, 0, 8);

    /* Find min/max color */
    mn = mx = block[3];
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            int val = block[3 + x * 4 + y * stride];
            if (val < mn)
                mn = val;
            else if (val > mx)
                mx = val;
        }
    }

    /* Encode them */
    dst[0] = (uint8_t) mx;
    dst[1] = (uint8_t) mn;
    dst += 2;

    /* Mono-alpha shortcut */
    if (mn == mx)
        return;

    /* Determine bias and emit color indices.
     * Given the choice of mx/mn, these indices are optimal:
     * fgiesen.wordpress.com/2009/12/15/dxt5-alpha-block-index-determination */
    dist = mx - mn;

    dist4 = dist * 4;
    dist2 = dist * 2;
    if (dist < 8)
        bias = dist - 1 - mn * 7;
    else
        bias = dist / 2 + 2 - mn * 7;

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            int alp = block[3 + x * 4 + y * stride] * 7 + bias;
            int ind, tmp;

            /* This is a "linear scale" lerp factor between 0 (val=min)
             * and 7 (val=max) to select index. */
            tmp  = (alp >= dist4) ? -1 : 0;
            ind  = tmp & 4;
            alp -= dist4 & tmp;
            tmp  = (alp >= dist2) ? -1 : 0;
            ind += tmp & 2;
            alp -= dist2 & tmp;
            ind += (alp >= dist);

            /* Turn linear scale into DXT index (0/1 are extreme points) */
            ind  = -ind & 7;
            ind ^= (2 > ind);

            /* Write index */
            mask |= ind << bits;
            bits += 3;
            if (bits >= 8) {
                *dst++ = mask;
                mask >>= 8;
                bits  -= 8;
            }
        }
    }
}