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
struct kpc_running_remote {int classes; int /*<<< orphan*/  cfg_state_mask; int /*<<< orphan*/  cfg_target_mask; } ;

/* Variables and functions */
 int KPC_CLASS_FIXED_MASK ; 
 int /*<<< orphan*/  assert (struct kpc_running_remote*) ; 
 scalar_t__ kpc_controls_fixed_counters () ; 
 int /*<<< orphan*/  set_running_configurable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_running_fixed (int) ; 

__attribute__((used)) static void
kpc_set_running_mp_call( void *vstate )
{
	struct kpc_running_remote *mp_config = (struct kpc_running_remote*) vstate;
	assert(mp_config);

	if (kpc_controls_fixed_counters())
		set_running_fixed(mp_config->classes & KPC_CLASS_FIXED_MASK);

	set_running_configurable(mp_config->cfg_target_mask,
				 mp_config->cfg_state_mask);
}