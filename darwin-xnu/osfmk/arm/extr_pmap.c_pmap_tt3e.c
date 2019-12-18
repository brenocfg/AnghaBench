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
typedef  scalar_t__ vm_map_address_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int tt_entry_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int ARM_TTE_TABLE_MASK ; 
 int ARM_TTE_TYPE_BLOCK ; 
 int ARM_TTE_TYPE_MASK ; 
 int ARM_TTE_TYPE_TABLE ; 
 int ARM_TTE_VALID ; 
 int* PT_ENTRY_NULL ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phystokv (int) ; 
 int* pmap_tt2e (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t tt3_index (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline pt_entry_t *
pmap_tt3e(
	 pmap_t pmap,
	 vm_map_address_t addr)
{
	pt_entry_t     *ptp;
	tt_entry_t     *ttp;
	tt_entry_t      tte;

	ttp = pmap_tt2e(pmap, addr);
	if (ttp == PT_ENTRY_NULL)
		return (PT_ENTRY_NULL);

	tte = *ttp;

#if MACH_ASSERT
	if ((tte & (ARM_TTE_TYPE_MASK | ARM_TTE_VALID)) == (ARM_TTE_TYPE_BLOCK | ARM_TTE_VALID))
		panic("Attempt to demote L2 block: pmap=%p, va=0x%llx, tte=0x%llx\n", pmap, (uint64_t)addr, (uint64_t)tte);
#endif
	if ((tte & (ARM_TTE_TYPE_MASK | ARM_TTE_VALID)) != (ARM_TTE_TYPE_TABLE | ARM_TTE_VALID)) {
		return (PT_ENTRY_NULL);
	}

	/* Get third-level (4KB) entry */
	ptp = &(((pt_entry_t*) phystokv(tte & ARM_TTE_TABLE_MASK))[tt3_index(pmap, addr)]);
	return (ptp);
}