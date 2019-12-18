#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int KPC_ALL_CPUS ; 
 int kpc_get_cpu_counters (int,int,int*,int*) ; 

__attribute__((used)) static int
sysctl_kpc_get_counters(uint32_t counters,
                      uint32_t *size, void *buf)
{
	uint64_t *ctr_buf = (uint64_t*)buf;
	int curcpu;
	uint32_t count;

	count = kpc_get_cpu_counters(counters & KPC_ALL_CPUS,
	                             counters,
	                             &curcpu, &ctr_buf[1]);
	if (!count)
		return EINVAL;

	ctr_buf[0] = curcpu;

	*size = (count+1) * sizeof(uint64_t);

	return 0;
}