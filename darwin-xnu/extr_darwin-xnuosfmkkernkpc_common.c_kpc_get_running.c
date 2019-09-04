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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  KPC_CLASS_CONFIGURABLE_MASK ; 
 int /*<<< orphan*/  KPC_CLASS_FIXED_MASK ; 
 int /*<<< orphan*/  KPC_CLASS_POWER_MASK ; 
 scalar_t__ kpc_get_configurable_pmc_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ kpc_is_running_configurable (scalar_t__) ; 
 scalar_t__ kpc_is_running_fixed () ; 

uint32_t
kpc_get_running(void)
{
	uint64_t pmc_mask = 0;
	uint32_t cur_state = 0;

	if (kpc_is_running_fixed())
		cur_state |= KPC_CLASS_FIXED_MASK;

	pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_CONFIGURABLE_MASK);
	if (kpc_is_running_configurable(pmc_mask))
		cur_state |= KPC_CLASS_CONFIGURABLE_MASK;

	pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_POWER_MASK);
	if ((pmc_mask != 0) && kpc_is_running_configurable(pmc_mask))
		cur_state |= KPC_CLASS_POWER_MASK;

	return cur_state;
}