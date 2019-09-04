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
typedef  int uint32_t ;

/* Variables and functions */
 int count_bits (int) ; 
 int* wp_log2_table ; 

__attribute__((used)) static uint32_t log2sample(uint32_t v, int limit, uint32_t *result)
{
    uint32_t dbits = count_bits(v);

    if ((v += v >> 9) < (1 << 8)) {
        *result += (dbits << 8) + wp_log2_table[(v << (9 - dbits)) & 0xff];
    } else {
        *result += dbits = (dbits << 8) + wp_log2_table[(v >> (dbits - 9)) & 0xff];

        if (limit && dbits >= limit)
            return 1;
    }

    return 0;
}