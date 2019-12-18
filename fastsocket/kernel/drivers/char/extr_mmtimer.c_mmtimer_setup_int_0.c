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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  HUB_S (unsigned long*,unsigned long) ; 
 scalar_t__ LOCAL_MMR_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ SGI_MMTIMER_VECTOR ; 
 int /*<<< orphan*/  SH_INT_CMPB ; 
 int /*<<< orphan*/  SH_RTC1_INT_CONFIG ; 
 unsigned long SH_RTC1_INT_CONFIG_IDX_SHFT ; 
 unsigned long SH_RTC1_INT_CONFIG_PID_SHFT ; 
 int /*<<< orphan*/  SH_RTC1_INT_ENABLE ; 
 scalar_t__ cpu_physical_id (int) ; 
 int /*<<< orphan*/  mmtimer_clr_int_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmtimer_setup_int_0(int cpu, u64 expires)
{
	u64 val;

	/* Disable interrupt */
	HUB_S((u64 *)LOCAL_MMR_ADDR(SH_RTC1_INT_ENABLE), 0UL);

	/* Initialize comparator value */
	HUB_S((u64 *)LOCAL_MMR_ADDR(SH_INT_CMPB), -1L);

	/* Clear pending bit */
	mmtimer_clr_int_pending(0);

	val = ((u64)SGI_MMTIMER_VECTOR << SH_RTC1_INT_CONFIG_IDX_SHFT) |
		((u64)cpu_physical_id(cpu) <<
			SH_RTC1_INT_CONFIG_PID_SHFT);

	/* Set configuration */
	HUB_S((u64 *)LOCAL_MMR_ADDR(SH_RTC1_INT_CONFIG), val);

	/* Enable RTC interrupts */
	HUB_S((u64 *)LOCAL_MMR_ADDR(SH_RTC1_INT_ENABLE), 1UL);

	/* Initialize comparator value */
	HUB_S((u64 *)LOCAL_MMR_ADDR(SH_INT_CMPB), expires);


}