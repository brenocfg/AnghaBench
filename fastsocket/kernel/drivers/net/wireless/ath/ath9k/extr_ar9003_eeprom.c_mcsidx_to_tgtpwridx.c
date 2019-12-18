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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 mcsidx_to_tgtpwridx(unsigned int mcs_idx, u8 base_pwridx)
{
	u8 mod_idx = mcs_idx % 8;

	if (mod_idx <= 3)
		return mod_idx ? (base_pwridx + 1) : base_pwridx;
	else
		return base_pwridx + 4 * (mcs_idx / 8) + mod_idx - 2;
}