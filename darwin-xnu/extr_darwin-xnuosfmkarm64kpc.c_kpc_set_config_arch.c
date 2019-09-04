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
typedef  size_t uint32_t ;
struct kpc_config_remote {struct kpc_config_remote* configv; int /*<<< orphan*/  pmc_mask; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (struct kpc_config_remote*) ; 
 int /*<<< orphan*/  config_in_whitelist (struct kpc_config_remote) ; 
 int /*<<< orphan*/  cpu_broadcast_xcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kpc_config_remote*) ; 
 int /*<<< orphan*/  kpc_config_sync ; 
 int kpc_configured ; 
 size_t kpc_popcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_set_config_xcall ; 
 int /*<<< orphan*/  whitelist_disabled ; 

int
kpc_set_config_arch(struct kpc_config_remote *mp_config)
{
	uint32_t count = kpc_popcount(mp_config->pmc_mask);

	assert(mp_config);
	assert(mp_config->configv);

	/* check config against whitelist for external devs */
	for (uint32_t i = 0; i < count; ++i) {
		if (!whitelist_disabled && !config_in_whitelist(mp_config->configv[i])) {
			return EPERM;
		}
	}

	/* dispatch to all CPUs */
	cpu_broadcast_xcall(&kpc_config_sync, TRUE, kpc_set_config_xcall, mp_config);

	kpc_configured = 1;

	return 0;
}