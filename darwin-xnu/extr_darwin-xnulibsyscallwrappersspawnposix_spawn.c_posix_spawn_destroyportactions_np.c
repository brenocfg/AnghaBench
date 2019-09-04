#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
typedef  int /*<<< orphan*/ * _posix_spawn_port_actions_t ;
struct TYPE_2__ {int /*<<< orphan*/ * psa_ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
posix_spawn_destroyportactions_np(posix_spawnattr_t *attr)
{
	_posix_spawnattr_t psattr;
	_posix_spawn_port_actions_t acts; 

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;
	acts = psattr->psa_ports; 
	if (acts == NULL)
		return EINVAL;
	
	free(acts);
	return 0;
}