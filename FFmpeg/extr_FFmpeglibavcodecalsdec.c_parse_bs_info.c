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
typedef  unsigned int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void parse_bs_info(const uint32_t bs_info, unsigned int n,
                          unsigned int div, unsigned int **div_blocks,
                          unsigned int *num_blocks)
{
    if (n < 31 && ((bs_info << n) & 0x40000000)) {
        // if the level is valid and the investigated bit n is set
        // then recursively check both children at bits (2n+1) and (2n+2)
        n   *= 2;
        div += 1;
        parse_bs_info(bs_info, n + 1, div, div_blocks, num_blocks);
        parse_bs_info(bs_info, n + 2, div, div_blocks, num_blocks);
    } else {
        // else the bit is not set or the last level has been reached
        // (bit implicitly not set)
        **div_blocks = div;
        (*div_blocks)++;
        (*num_blocks)++;
    }
}