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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint32_t set_cnt_in_reg(int bit_start_in_reg, int bit_count_used_in_reg, uint32_t reg_masked, size_t* cnt)
{
    assert((bit_start_in_reg + bit_count_used_in_reg) <= 32);
    uint32_t reg_to_write = 0;
    for (int i = bit_start_in_reg; i < bit_start_in_reg + bit_count_used_in_reg; ++i) {
        if ((reg_masked & (1 << i)) == 0) {
            reg_to_write |= (1 << i);
            if (--(*cnt) == 0) {
                break;
            }
        }
    }
    return reg_to_write;
}