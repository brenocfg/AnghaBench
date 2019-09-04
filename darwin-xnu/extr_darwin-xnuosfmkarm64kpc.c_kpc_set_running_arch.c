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
struct kpc_running_remote {int /*<<< orphan*/  classes; int /*<<< orphan*/  cfg_state_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_broadcast_xcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kpc_running_remote*) ; 
 int kpc_configured ; 
 int /*<<< orphan*/  kpc_running_cfg_pmc_mask ; 
 int /*<<< orphan*/  kpc_running_classes ; 
 int /*<<< orphan*/  kpc_set_running_xcall ; 
 int /*<<< orphan*/  kpc_xcall_sync ; 

int
kpc_set_running_arch(struct kpc_running_remote *mp_config)
{
	assert(mp_config != NULL);

	/* dispatch to all CPUs */
	cpu_broadcast_xcall(&kpc_xcall_sync, TRUE, kpc_set_running_xcall, mp_config);

	kpc_running_cfg_pmc_mask = mp_config->cfg_state_mask;
	kpc_running_classes = mp_config->classes;
	kpc_configured = 1;

	return 0;
}