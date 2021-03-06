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
struct TYPE_2__ {int /*<<< orphan*/  fixed_ranges; } ;

/* Variables and functions */
 scalar_t__ cpu_has_mtrr ; 
 int /*<<< orphan*/  get_fixed_ranges (int /*<<< orphan*/ ) ; 
 TYPE_1__ mtrr_state ; 

void mtrr_save_fixed_ranges(void *info)
{
	if (cpu_has_mtrr)
		get_fixed_ranges(mtrr_state.fixed_ranges);
}