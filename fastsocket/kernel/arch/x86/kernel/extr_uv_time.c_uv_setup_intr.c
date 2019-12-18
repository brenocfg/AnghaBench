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
typedef  long u64 ;

/* Variables and functions */
 long UV1H_EVENT_OCCURRED0_RTC1_MASK ; 
 int /*<<< orphan*/  UVH_EVENT_OCCURRED0_ALIAS ; 
 int /*<<< orphan*/  UVH_INT_CMPB ; 
 int /*<<< orphan*/  UVH_RTC1_INT_CONFIG ; 
 long UVH_RTC1_INT_CONFIG_APIC_ID_SHFT ; 
 long UVH_RTC1_INT_CONFIG_M_MASK ; 
 long UVH_RTC1_INT_CONFIG_VECTOR_SHFT ; 
 int /*<<< orphan*/  UVXH_EVENT_OCCURRED2_ALIAS ; 
 long UVXH_EVENT_OCCURRED2_RTC_1_MASK ; 
 long X86_PLATFORM_IPI_VECTOR ; 
 unsigned long cpu_physical_id (int) ; 
 scalar_t__ is_uv1_hub () ; 
 unsigned long uv_apicid_hibits ; 
 int uv_cpu_to_pnode (int) ; 
 int /*<<< orphan*/  uv_intr_pending (int) ; 
 long uv_read_rtc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_write_global_mmr64 (int,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int uv_setup_intr(int cpu, u64 expires)
{
	u64 val;
	unsigned long apicid = cpu_physical_id(cpu) | uv_apicid_hibits;
	int pnode = uv_cpu_to_pnode(cpu);

	uv_write_global_mmr64(pnode, UVH_RTC1_INT_CONFIG,
		UVH_RTC1_INT_CONFIG_M_MASK);
	uv_write_global_mmr64(pnode, UVH_INT_CMPB, -1L);

	if (is_uv1_hub())
		uv_write_global_mmr64(pnode, UVH_EVENT_OCCURRED0_ALIAS,
				UV1H_EVENT_OCCURRED0_RTC1_MASK);
	else
		uv_write_global_mmr64(pnode, UVXH_EVENT_OCCURRED2_ALIAS,
				UVXH_EVENT_OCCURRED2_RTC_1_MASK);

	val = (X86_PLATFORM_IPI_VECTOR << UVH_RTC1_INT_CONFIG_VECTOR_SHFT) |
		((u64)apicid << UVH_RTC1_INT_CONFIG_APIC_ID_SHFT);

	/* Set configuration */
	uv_write_global_mmr64(pnode, UVH_RTC1_INT_CONFIG, val);
	/* Initialize comparator value */
	uv_write_global_mmr64(pnode, UVH_INT_CMPB, expires);

	if (uv_read_rtc(NULL) <= expires)
		return 0;

	return !uv_intr_pending(pnode);
}