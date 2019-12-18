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
struct TYPE_2__ {int psa_thread_limit; } ;

/* Variables and functions */
 int EINVAL ; 

int
posix_spawnattr_set_threadlimit_ext(posix_spawnattr_t * __restrict attr,
	int thread_limit)
{
	_posix_spawnattr_t psattr;

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;

	psattr->psa_thread_limit = thread_limit;

	return (0);

}