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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  rgtc_block_internal (int*,int /*<<< orphan*/ ,int const*,int*,int,int,int) ; 

__attribute__((used)) static inline void rgtc1_block_internal(uint8_t *dst, ptrdiff_t stride,
                                        const uint8_t *block, int sign, int mono, int offset, int pix_size)
{
    int color_table[8];
    int r0, r1;

    if (sign) {
        /* signed data is in [-128 127] so just offset it to unsigned
         * and it can be treated exactly the same */
        r0 = ((int8_t) block[0]) + 128;
        r1 = ((int8_t) block[1]) + 128;
    } else {
        r0 = block[0];
        r1 = block[1];
    }

    color_table[0] = r0;
    color_table[1] = r1;

    if (r0 > r1) {
        /* 6 interpolated color values */
        color_table[2] = (6 * r0 + 1 * r1) / 7; // bit code 010
        color_table[3] = (5 * r0 + 2 * r1) / 7; // bit code 011
        color_table[4] = (4 * r0 + 3 * r1) / 7; // bit code 100
        color_table[5] = (3 * r0 + 4 * r1) / 7; // bit code 101
        color_table[6] = (2 * r0 + 5 * r1) / 7; // bit code 110
        color_table[7] = (1 * r0 + 6 * r1) / 7; // bit code 111
    } else {
        /* 4 interpolated color values */
        color_table[2] = (4 * r0 + 1 * r1) / 5; // bit code 010
        color_table[3] = (3 * r0 + 2 * r1) / 5; // bit code 011
        color_table[4] = (2 * r0 + 3 * r1) / 5; // bit code 100
        color_table[5] = (1 * r0 + 4 * r1) / 5; // bit code 101
        color_table[6] = 0;    /* min range */  // bit code 110
        color_table[7] = 255;  /* max range */  // bit code 111
    }

    rgtc_block_internal(dst, stride, block, color_table, mono, offset, pix_size);
}