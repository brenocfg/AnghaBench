#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_state_flavor_t ;
typedef  int /*<<< orphan*/  posix_spawnattr_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  exception_mask_t ;
typedef  int /*<<< orphan*/  exception_behavior_t ;
struct TYPE_3__ {int /*<<< orphan*/  flavor; int /*<<< orphan*/  behavior; int /*<<< orphan*/  new_port; int /*<<< orphan*/  mask; int /*<<< orphan*/  port_type; } ;
typedef  TYPE_1__ _ps_port_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSPA_EXCEPTION ; 
 int posix_spawn_appendportaction_np (int /*<<< orphan*/ *,TYPE_1__*) ; 

int    
posix_spawnattr_setexceptionports_np(
		posix_spawnattr_t       *attr,
		exception_mask_t        mask,
		mach_port_t              new_port,
		exception_behavior_t    behavior,
		thread_state_flavor_t   flavor)
{
	_ps_port_action_t action = {
		.port_type = PSPA_EXCEPTION,
		.mask = mask,
		.new_port = new_port,
		.behavior = behavior,
		.flavor = flavor,
	};
	return posix_spawn_appendportaction_np(attr, &action);
}