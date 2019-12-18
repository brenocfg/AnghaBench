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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  tt_entry_t ;

/* Variables and functions */
 int L1_TABLE_INDEX (int /*<<< orphan*/ ) ; 
 int L2_TABLE_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * L2_TABLE_VA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cpu_tte ; 

tt_entry_t *
arm_kva_to_tte(vm_offset_t va)
{
#if __ARM64_TWO_LEVEL_PMAP__
	tt_entry_t *tte2;
	tte2 = cpu_tte + L2_TABLE_INDEX(va);
#else
	tt_entry_t *tte1, *tte2;
	tte1 = cpu_tte + L1_TABLE_INDEX(va);
	tte2 = L2_TABLE_VA(tte1) + L2_TABLE_INDEX(va);
#endif
	return tte2;
}