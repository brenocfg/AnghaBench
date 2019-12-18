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
typedef  int /*<<< orphan*/  posix_spawnattr_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
struct TYPE_3__ {int /*<<< orphan*/  new_port; int /*<<< orphan*/  port_type; } ;
typedef  TYPE_1__ _ps_port_action_t ;

/* Variables and functions */
 int EINVAL ; 
 int POSIX_SPAWN_IMPORTANCE_PORT_COUNT ; 
 int /*<<< orphan*/  PSPA_IMP_WATCHPORTS ; 
 int posix_spawn_appendportaction_np (int /*<<< orphan*/ *,TYPE_1__*) ; 

int     
posix_spawnattr_set_importancewatch_port_np(posix_spawnattr_t * __restrict attr,
                 int count, mach_port_t portarray[]) 
{
	int err = 0, i;

	if (count < 0 || count > POSIX_SPAWN_IMPORTANCE_PORT_COUNT) {
		return EINVAL;
	}

	for (i = 0; i < count; i++) {
		_ps_port_action_t action = {
			.port_type = PSPA_IMP_WATCHPORTS,
			.new_port = portarray[i],
		};
		int err = posix_spawn_appendportaction_np(attr, &action);
		if (err) {
			break;
		}
	}
	return err;
}