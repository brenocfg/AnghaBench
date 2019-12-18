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
typedef  int /*<<< orphan*/  cpu_type_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * psa_binprefs; } ;

/* Variables and functions */
 int EINVAL ; 

int
posix_spawnattr_setbinpref_np(posix_spawnattr_t * __restrict attr,
		size_t count, cpu_type_t *pref, size_t * __restrict ocount)
{
	_posix_spawnattr_t psattr;
	int i = 0;

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;
	for (i = 0; i < count && i < 4; i++) {
		psattr->psa_binprefs[i] = pref[i];
	}

	/* return number of binprefs copied over */
	if (ocount)
		*ocount = i;
	return 0;
}