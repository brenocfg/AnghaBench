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
struct kpc_config_remote {int classes; int /*<<< orphan*/  pmc_mask; struct kpc_config_remote* configv; } ;
typedef  struct kpc_config_remote kpc_config_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_FIXED_MASK ; 
 int /*<<< orphan*/  assert (struct kpc_config_remote*) ; 
 scalar_t__ kpc_get_config_count (int) ; 
 scalar_t__ kpc_popcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_set_configurable_config (struct kpc_config_remote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_set_fixed_config (struct kpc_config_remote*) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kpc_set_config_mp_call(void *vmp_config)
{

	struct kpc_config_remote *mp_config = vmp_config;
	kpc_config_t *new_config = NULL;
	uint32_t classes = 0, count = 0;
	boolean_t enabled;

	assert(mp_config);
	assert(mp_config->configv);
	classes = mp_config->classes;
	new_config = mp_config->configv;

	enabled = ml_set_interrupts_enabled(FALSE);
	
	if (classes & KPC_CLASS_FIXED_MASK)
	{
		kpc_set_fixed_config(&new_config[count]);
		count += kpc_get_config_count(KPC_CLASS_FIXED_MASK);
	}

	if (classes & KPC_CLASS_CONFIGURABLE_MASK) {
		kpc_set_configurable_config(&new_config[count], mp_config->pmc_mask);
		count += kpc_popcount(mp_config->pmc_mask);
	}

	ml_set_interrupts_enabled(enabled);
}