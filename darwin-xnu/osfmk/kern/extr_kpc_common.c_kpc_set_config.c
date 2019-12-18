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
struct kpc_config_remote {int classes; int /*<<< orphan*/  pmc_mask; int /*<<< orphan*/ * configv; } ;
typedef  int /*<<< orphan*/  kpc_config_t ;

/* Variables and functions */
 int EPERM ; 
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_POWER_MASK ; 
 int KPC_CLASS_RAWPMU_MASK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kpc_config_lock ; 
 int /*<<< orphan*/  kpc_get_configurable_pmc_mask (int) ; 
 scalar_t__ kpc_multiple_clients () ; 
 int kpc_set_config_arch (struct kpc_config_remote*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

int
kpc_set_config(uint32_t classes, kpc_config_t *configv)
{
	int ret = 0;
	struct kpc_config_remote mp_config = {
		.classes = classes, .configv = configv,
		.pmc_mask = kpc_get_configurable_pmc_mask(classes)
	};

	assert(configv);

	/* don't allow RAWPMU configuration when sharing counters */
	if ((classes & KPC_CLASS_RAWPMU_MASK) && kpc_multiple_clients()) {
		return EPERM;
	}

	/* no clients have the right to modify both classes */
	if ((classes & (KPC_CLASS_CONFIGURABLE_MASK)) &&
	    (classes & (KPC_CLASS_POWER_MASK)))
	{
		return EPERM;
	}

	lck_mtx_lock(&kpc_config_lock);

	/* translate the power class for the machine layer */
	if (classes & KPC_CLASS_POWER_MASK)
		mp_config.classes |= KPC_CLASS_CONFIGURABLE_MASK;

	ret = kpc_set_config_arch( &mp_config );

	lck_mtx_unlock(&kpc_config_lock);

	return ret;
}