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
 int AV_RL24 (int const*) ; 

__attribute__((used)) static void decompress_indices(uint8_t *dst, const uint8_t *src)
{
    int block, i;

    for (block = 0; block < 2; block++) {
        int tmp = AV_RL24(src);

        /* Unpack 8x3 bit from last 3 byte block */
        for (i = 0; i < 8; i++)
            dst[i] = (tmp >> (i * 3)) & 0x7;

        src += 3;
        dst += 8;
    }
}