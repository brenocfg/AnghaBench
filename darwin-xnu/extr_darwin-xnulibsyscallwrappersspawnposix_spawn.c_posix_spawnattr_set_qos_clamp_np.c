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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
struct TYPE_2__ {scalar_t__ psa_qos_clamp; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ POSIX_SPAWN_PROC_CLAMP_LAST ; 

int posix_spawnattr_set_qos_clamp_np(const posix_spawnattr_t * __restrict attr, uint64_t qos_clamp)
{
	_posix_spawnattr_t psattr;

	if (attr == NULL || *attr == NULL) {
		return EINVAL;
	}

	if (qos_clamp >= POSIX_SPAWN_PROC_CLAMP_LAST)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;
	psattr->psa_qos_clamp = qos_clamp;

	return 0;
}