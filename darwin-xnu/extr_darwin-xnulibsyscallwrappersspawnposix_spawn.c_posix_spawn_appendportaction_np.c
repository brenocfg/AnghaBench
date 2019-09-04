#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  int /*<<< orphan*/  _ps_port_action_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
typedef  TYPE_2__* _posix_spawn_port_actions_t ;
struct TYPE_4__ {size_t pspa_alloc; size_t pspa_count; int /*<<< orphan*/ * pspa_actions; } ;
struct TYPE_3__ {TYPE_2__* psa_ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int posix_spawn_createportactions_np (int /*<<< orphan*/ **) ; 
 int posix_spawn_growportactions_np (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
posix_spawn_appendportaction_np(posix_spawnattr_t *attr, _ps_port_action_t *act)
{
	_posix_spawnattr_t psattr;
	_posix_spawn_port_actions_t acts;

	if (attr == NULL || *attr == NULL || act == NULL) {
		return EINVAL;
	}

	psattr = *(_posix_spawnattr_t *)attr;
	acts = psattr->psa_ports;

	// Have any port actions been created yet?
	if (acts == NULL) {
		int err = posix_spawn_createportactions_np(attr);
		if (err) {
			return err;
		}
		acts = psattr->psa_ports;
	}

	// Is there enough room?
	if (acts->pspa_alloc == acts->pspa_count) {
		int err = posix_spawn_growportactions_np(attr);
		if (err) {
			return err;
		}
		acts = psattr->psa_ports;
	}

	// Add this action to next spot in array
	acts->pspa_actions[acts->pspa_count] = *act;
	acts->pspa_count++;

	return 0;
}