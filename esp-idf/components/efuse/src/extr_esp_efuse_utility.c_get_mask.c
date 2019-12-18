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

__attribute__((used)) static uint32_t get_mask(unsigned int bit_count, unsigned int shift)
{
    uint32_t mask;
    if (bit_count != 32) {
        mask = (1 << bit_count) - 1;
    } else {
        mask = 0xFFFFFFFF;
    }
    return mask << shift;
}