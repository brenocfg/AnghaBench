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
typedef  int uint32_t ;
struct kpc_running_remote {int classes; unsigned long long cfg_target_mask; unsigned long long cfg_state_mask; } ;

/* Variables and functions */
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_POWER_MASK ; 
 void* kpc_get_configurable_pmc_mask (int) ; 
 int kpc_set_running_arch (struct kpc_running_remote*) ; 

int
kpc_set_running(uint32_t classes)
{
	uint32_t all_cfg_classes = KPC_CLASS_CONFIGURABLE_MASK | KPC_CLASS_POWER_MASK;
	struct kpc_running_remote mp_config = {
		.classes = classes, .cfg_target_mask= 0ULL, .cfg_state_mask = 0ULL
	};

	/* target all available PMCs */
	mp_config.cfg_target_mask = kpc_get_configurable_pmc_mask(all_cfg_classes);

	/* translate the power class for the machine layer */
	if (classes & KPC_CLASS_POWER_MASK)
		mp_config.classes |= KPC_CLASS_CONFIGURABLE_MASK;

	/* generate the state of each configurable PMCs */
	mp_config.cfg_state_mask = kpc_get_configurable_pmc_mask(classes);

	return kpc_set_running_arch(&mp_config);
}