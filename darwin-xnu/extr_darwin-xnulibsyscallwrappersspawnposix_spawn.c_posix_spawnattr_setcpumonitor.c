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
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
struct TYPE_2__ {void* psa_cpumonitor_interval; void* psa_cpumonitor_percent; } ;

/* Variables and functions */
 int EINVAL ; 

int
posix_spawnattr_setcpumonitor(posix_spawnattr_t * __restrict attr,
		uint64_t percent, uint64_t interval)
{
	_posix_spawnattr_t psattr;

	if (attr == NULL || *attr == NULL)
		return (EINVAL);

	psattr = *(_posix_spawnattr_t *)attr;

	psattr->psa_cpumonitor_percent = percent;
	psattr->psa_cpumonitor_interval = interval;

	return (0);			
}