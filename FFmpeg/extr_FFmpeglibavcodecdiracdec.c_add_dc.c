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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_BLOCKSIZE ; 

__attribute__((used)) static void add_dc(uint16_t *dst, int dc, int stride,
                   uint8_t *obmc_weight, int xblen, int yblen)
{
    int x, y;
    dc += 128;

    for (y = 0; y < yblen; y++) {
        for (x = 0; x < xblen; x += 2) {
            dst[x  ] += dc * obmc_weight[x  ];
            dst[x+1] += dc * obmc_weight[x+1];
        }
        dst          += stride;
        obmc_weight  += MAX_BLOCKSIZE;
    }
}