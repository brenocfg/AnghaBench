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
typedef  TYPE_1__* _posix_spawnattr_t ;
typedef  TYPE_2__* _posix_spawn_port_actions_t ;
struct TYPE_4__ {int pspa_alloc; scalar_t__ pspa_count; } ;
struct TYPE_3__ {TYPE_2__* psa_ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PS_PORT_ACTIONS_SIZE (int) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
posix_spawn_createportactions_np(posix_spawnattr_t *attr)
{
	_posix_spawnattr_t psattr;
	_posix_spawn_port_actions_t acts;

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;
	acts = (_posix_spawn_port_actions_t)malloc(PS_PORT_ACTIONS_SIZE(2));
	if (acts == NULL)
		return ENOMEM;
	
	acts->pspa_alloc = 2;
	acts->pspa_count = 0;

	psattr->psa_ports = acts;
	return 0;
}