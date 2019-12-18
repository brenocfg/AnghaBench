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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  LE_CENTRIC_MUL (int*,int const*,int,unsigned int) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mcdc(uint16_t *dst, const uint16_t *src, int log2w,
                        int h, int stride, int scale, unsigned dc)
{
    int i;
    dc *= 0x10001;

    switch (log2w) {
    case 0:
        for (i = 0; i < h; i++) {
            dst[0] = scale * src[0] + dc;
            if (scale)
                src += stride;
            dst += stride;
        }
        break;
    case 1:
        for (i = 0; i < h; i++) {
            LE_CENTRIC_MUL(dst, src, scale, dc);
            if (scale)
                src += stride;
            dst += stride;
        }
        break;
    case 2:
        for (i = 0; i < h; i++) {
            LE_CENTRIC_MUL(dst, src, scale, dc);
            LE_CENTRIC_MUL(dst + 2, src + 2, scale, dc);
            if (scale)
                src += stride;
            dst += stride;
        }
        break;
    case 3:
        for (i = 0; i < h; i++) {
            LE_CENTRIC_MUL(dst,     src,     scale, dc);
            LE_CENTRIC_MUL(dst + 2, src + 2, scale, dc);
            LE_CENTRIC_MUL(dst + 4, src + 4, scale, dc);
            LE_CENTRIC_MUL(dst + 6, src + 6, scale, dc);
            if (scale)
                src += stride;
            dst += stride;
        }
        break;
    default:
        av_assert0(0);
    }
}