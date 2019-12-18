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

/* Variables and functions */
 long cpu_physical_id (int) ; 
 int cpuid_to_nasid (int) ; 
 int /*<<< orphan*/  ia64_sn_get_sapic_info (long,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_send_IPI_phys (int,long,int,int) ; 
 scalar_t__ unlikely (int) ; 

void sn2_send_IPI(int cpuid, int vector, int delivery_mode, int redirect)
{
	long physid;
	int nasid;

	physid = cpu_physical_id(cpuid);
	nasid = cpuid_to_nasid(cpuid);

	/* the following is used only when starting cpus at boot time */
	if (unlikely(nasid == -1))
		ia64_sn_get_sapic_info(physid, &nasid, NULL, NULL);

	sn_send_IPI_phys(nasid, physid, vector, delivery_mode);
}