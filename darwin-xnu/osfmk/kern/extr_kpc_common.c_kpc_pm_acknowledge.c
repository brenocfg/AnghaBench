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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ force_all_ctrs ; 
 int kpc_calling_pm ; 

void
kpc_pm_acknowledge(boolean_t available_to_pm)
{
	/*
	 * Force-all-counters should still be true when the counters are being
	 * made available to power management and false when counters are going
	 * to be taken away.
	 */
	assert(force_all_ctrs == available_to_pm);
	/*
	 * Make sure power management isn't playing games with us.
	 */
	assert(kpc_calling_pm == true);

	/*
	 * Counters being available means no one is forcing all counters.
	 */
	force_all_ctrs = available_to_pm ? FALSE : TRUE;
}