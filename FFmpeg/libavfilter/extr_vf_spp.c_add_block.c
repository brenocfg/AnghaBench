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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static inline void add_block(uint16_t *dst, int linesize, const int16_t block[64])
{
    int y;

    for (y = 0; y < 8; y++) {
        *(uint32_t *)&dst[0 + y*linesize] += *(uint32_t *)&block[0 + y*8];
        *(uint32_t *)&dst[2 + y*linesize] += *(uint32_t *)&block[2 + y*8];
        *(uint32_t *)&dst[4 + y*linesize] += *(uint32_t *)&block[4 + y*8];
        *(uint32_t *)&dst[6 + y*linesize] += *(uint32_t *)&block[6 + y*8];
    }
}