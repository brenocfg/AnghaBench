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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct kpc_config_remote {int classes; int /*<<< orphan*/  pmc_mask; int /*<<< orphan*/ * configv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_FIXED_MASK ; 
 int KPC_CLASS_POWER_MASK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kpc_config_lock ; 
 int /*<<< orphan*/  kpc_controls_fixed_counters () ; 
 int /*<<< orphan*/  kpc_get_configurable_pmc_mask (int) ; 
 int /*<<< orphan*/  kpc_set_period_arch (struct kpc_config_remote*) ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

int
kpc_set_period(uint32_t classes, uint64_t *val)
{
	struct kpc_config_remote mp_config = {
		.classes = classes, .configv = val,
		.pmc_mask = kpc_get_configurable_pmc_mask(classes)
	};

	assert(val);

	/* no clients have the right to modify both classes */
	if ((classes & (KPC_CLASS_CONFIGURABLE_MASK)) &&
	    (classes & (KPC_CLASS_POWER_MASK)))
	{
		return EPERM;
	}

	lck_mtx_lock(&kpc_config_lock);

#ifdef FIXED_COUNTER_SHADOW
	if ((classes & KPC_CLASS_FIXED_MASK) && !kpc_controls_fixed_counters()) {
		lck_mtx_unlock(&kpc_config_lock);
		return EPERM;
	}
# else
	if (classes & KPC_CLASS_FIXED_MASK) {
		lck_mtx_unlock(&kpc_config_lock);
		return EINVAL;
	}
#endif

	/* translate the power class for the machine layer */
	if (classes & KPC_CLASS_POWER_MASK)
		mp_config.classes |= KPC_CLASS_CONFIGURABLE_MASK;

	kprintf("setting period %u\n", classes);
	kpc_set_period_arch( &mp_config );

	lck_mtx_unlock(&kpc_config_lock);

	return 0;
}