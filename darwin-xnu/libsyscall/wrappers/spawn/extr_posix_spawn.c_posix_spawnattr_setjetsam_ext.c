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
struct TYPE_2__ {short psa_jetsam_flags; int psa_priority; int psa_memlimit_active; int psa_memlimit_inactive; } ;

/* Variables and functions */
 int EINVAL ; 
 short POSIX_SPAWN_JETSAM_SET ; 

int
posix_spawnattr_setjetsam_ext(posix_spawnattr_t * __restrict attr,
	short flags, int priority, int memlimit_active, int memlimit_inactive)
{
	_posix_spawnattr_t psattr;

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;

	psattr->psa_jetsam_flags = flags;
	psattr->psa_jetsam_flags |= POSIX_SPAWN_JETSAM_SET;
	psattr->psa_priority = priority;
	psattr->psa_memlimit_active = memlimit_active;
	psattr->psa_memlimit_inactive = memlimit_inactive;

	return (0);
}