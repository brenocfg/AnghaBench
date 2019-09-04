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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* ff_square_tab ; 

__attribute__((used)) static int pix_norm1_c(uint8_t *pix, int line_size)
{
    int s = 0, i, j;
    const uint32_t *sq = ff_square_tab + 256;

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j += 8) {
#if HAVE_FAST_64BIT
            register uint64_t x = *(uint64_t *) pix;
            s += sq[x         & 0xff];
            s += sq[(x >>  8) & 0xff];
            s += sq[(x >> 16) & 0xff];
            s += sq[(x >> 24) & 0xff];
            s += sq[(x >> 32) & 0xff];
            s += sq[(x >> 40) & 0xff];
            s += sq[(x >> 48) & 0xff];
            s += sq[(x >> 56) & 0xff];
#else
            register uint32_t x = *(uint32_t *) pix;
            s += sq[x         & 0xff];
            s += sq[(x >>  8) & 0xff];
            s += sq[(x >> 16) & 0xff];
            s += sq[(x >> 24) & 0xff];
            x  = *(uint32_t *) (pix + 4);
            s += sq[x         & 0xff];
            s += sq[(x >>  8) & 0xff];
            s += sq[(x >> 16) & 0xff];
            s += sq[(x >> 24) & 0xff];
#endif
            pix += 8;
        }
        pix += line_size - 16;
    }
    return s;
}