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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MSRS_IN_RANGE ; 
 int NUM_MSR_MAPS ; 
 unsigned int* msrpm_ranges ; 

__attribute__((used)) static void set_msr_interception(u32 *msrpm, unsigned msr,
				 int read, int write)
{
	int i;

	for (i = 0; i < NUM_MSR_MAPS; i++) {
		if (msr >= msrpm_ranges[i] &&
		    msr < msrpm_ranges[i] + MSRS_IN_RANGE) {
			u32 msr_offset = (i * MSRS_IN_RANGE + msr -
					  msrpm_ranges[i]) * 2;

			u32 *base = msrpm + (msr_offset / 32);
			u32 msr_shift = msr_offset % 32;
			u32 mask = ((write) ? 0 : 2) | ((read) ? 0 : 1);
			*base = (*base & ~(0x3 << msr_shift)) |
				(mask << msr_shift);
			return;
		}
	}
	BUG();
}