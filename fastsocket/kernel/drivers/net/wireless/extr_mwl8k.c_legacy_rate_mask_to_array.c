#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 TYPE_1__* mwl8k_rates_24 ; 

__attribute__((used)) static void legacy_rate_mask_to_array(u8 *rates, u32 mask)
{
	int i;
	int j;

	/*
	 * Clear nonstandard rate 4.
	 */
	mask &= 0x1fef;

	for (i = 0, j = 0; i < 13; i++) {
		if (mask & (1 << i))
			rates[j++] = mwl8k_rates_24[i].hw_value;
	}
}