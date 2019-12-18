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
typedef  unsigned int uint8_t ;

/* Variables and functions */

__attribute__((used)) static void blend_pixel(uint8_t *dst, unsigned src, unsigned alpha,
                        const uint8_t *mask, int mask_linesize, int l2depth,
                        unsigned w, unsigned h, unsigned shift, unsigned xm0)
{
    unsigned xm, x, y, t = 0;
    unsigned xmshf = 3 - l2depth;
    unsigned xmmod = 7 >> l2depth;
    unsigned mbits = (1 << (1 << l2depth)) - 1;
    unsigned mmult = 255 / mbits;

    for (y = 0; y < h; y++) {
        xm = xm0;
        for (x = 0; x < w; x++) {
            t += ((mask[xm >> xmshf] >> ((~xm & xmmod) << l2depth)) & mbits)
                 * mmult;
            xm++;
        }
        mask += mask_linesize;
    }
    alpha = (t >> shift) * alpha;
    *dst = ((0x1010101 - alpha) * *dst + alpha * src) >> 24;
}