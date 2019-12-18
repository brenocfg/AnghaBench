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
 int /*<<< orphan*/  UVH_IPI_INT ; 
 unsigned long UVH_IPI_INT_APIC_ID_SHFT ; 
 unsigned long UVH_IPI_INT_SEND_SHFT ; 
 unsigned long UVH_IPI_INT_VECTOR_SHFT ; 
 unsigned long X86_PLATFORM_IPI_VECTOR ; 
 unsigned long cpu_physical_id (int) ; 
 unsigned long uv_apicid_hibits ; 
 int uv_apicid_to_pnode (unsigned long) ; 
 int /*<<< orphan*/  uv_write_global_mmr64 (int,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void uv_rtc_send_IPI(int cpu)
{
	unsigned long apicid, val;
	int pnode;

	apicid = cpu_physical_id(cpu);
	pnode = uv_apicid_to_pnode(apicid);
	apicid |= uv_apicid_hibits;
	val = (1UL << UVH_IPI_INT_SEND_SHFT) |
	      (apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	      (X86_PLATFORM_IPI_VECTOR << UVH_IPI_INT_VECTOR_SHFT);

	uv_write_global_mmr64(pnode, UVH_IPI_INT, val);
}