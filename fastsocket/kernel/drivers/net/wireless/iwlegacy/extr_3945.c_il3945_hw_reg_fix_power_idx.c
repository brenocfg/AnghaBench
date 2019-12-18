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
 int IL_MAX_GAIN_ENTRIES ; 

__attribute__((used)) static inline u8
il3945_hw_reg_fix_power_idx(int idx)
{
	if (idx < 0)
		return 0;
	if (idx >= IL_MAX_GAIN_ENTRIES)
		return IL_MAX_GAIN_ENTRIES - 1;
	return (u8) idx;
}