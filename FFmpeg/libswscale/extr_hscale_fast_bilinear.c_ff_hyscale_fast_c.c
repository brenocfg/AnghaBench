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
typedef  int int16_t ;
typedef  int /*<<< orphan*/  SwsContext ;

/* Variables and functions */

void ff_hyscale_fast_c(SwsContext *c, int16_t *dst, int dstWidth,
                           const uint8_t *src, int srcW, int xInc)
{
    int i;
    unsigned int xpos = 0;
    for (i = 0; i < dstWidth; i++) {
        register unsigned int xx     = xpos >> 16;
        register unsigned int xalpha = (xpos & 0xFFFF) >> 9;
        dst[i] = (src[xx] << 7) + (src[xx + 1] - src[xx]) * xalpha;
        xpos  += xInc;
    }
    for (i=dstWidth-1; (i*xInc)>>16 >=srcW-1; i--)
        dst[i] = src[srcW-1]*128;
}