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
typedef  scalar_t__ m68k_reg ;
typedef  int /*<<< orphan*/  m68k_info ;

/* Variables and functions */
 int /*<<< orphan*/  add_reg_to_rw_list (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void update_bits_range(m68k_info *info, m68k_reg reg_start, uint8_t bits, int write)
{
	int i;

	for (i = 0; i < 8; ++i) {
		if (bits & (1 << i)) {
			add_reg_to_rw_list(info, reg_start + i, write);
		}
	}
}