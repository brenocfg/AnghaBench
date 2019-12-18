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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KPC_CLASS_CONFIGURABLE_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kpc_configurable_count () ; 
 scalar_t__ kpc_get_counter_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kpc_pm_handler ; 
 int /*<<< orphan*/  kpc_pm_has_custom_config ; 
 unsigned long long kpc_pm_pmc_mask ; 
 int /*<<< orphan*/  printf (char*) ; 

void
kpc_release_pm_counters(void)
{
	/* pre-condition */
	assert(kpc_pm_handler != NULL);

	/* release the counters */
	kpc_pm_has_custom_config = FALSE;
	kpc_pm_pmc_mask = 0ULL;
	kpc_pm_handler = NULL;

	printf("kpc: pm released counters\n");

	/* post-condition */
	assert(kpc_get_counter_count(KPC_CLASS_CONFIGURABLE_MASK) == kpc_configurable_count());
}