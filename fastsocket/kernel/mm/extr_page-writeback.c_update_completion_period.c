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

/* Variables and functions */
 int calc_period_shift () ; 
 int /*<<< orphan*/  prop_change_shift (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_completions ; 
 int /*<<< orphan*/  vm_dirties ; 

__attribute__((used)) static void update_completion_period(void)
{
	int shift = calc_period_shift();
	prop_change_shift(&vm_completions, shift);
	prop_change_shift(&vm_dirties, shift);
}