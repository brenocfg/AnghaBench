#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_map_address_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int tt_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_6__ {int* tte; } ;

/* Variables and functions */
 int ARM_TTE_TABLE_MASK ; 
 int ARM_TTE_TYPE_BLOCK ; 
 int ARM_TTE_TYPE_MASK ; 
 int ARM_TTE_TYPE_TABLE ; 
 int ARM_TTE_VALID ; 
 int* PT_ENTRY_NULL ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phystokv (int) ; 
 int* pmap_tt1e (TYPE_1__*,scalar_t__) ; 
 size_t tt2_index (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static inline tt_entry_t *
pmap_tt2e(pmap_t pmap,
	 vm_map_address_t addr)
{
#if __ARM64_TWO_LEVEL_PMAP__
	return (&pmap->tte[tt2_index(pmap, addr)]);
#else
	tt_entry_t     *ttp;
	tt_entry_t      tte;

	ttp = pmap_tt1e(pmap, addr);
	tte = *ttp;
	#if MACH_ASSERT
	if ((tte & (ARM_TTE_TYPE_MASK | ARM_TTE_VALID)) == (ARM_TTE_TYPE_BLOCK | ARM_TTE_VALID))
		panic("Attempt to demote L1 block (?!): pmap=%p, va=0x%llx, tte=0x%llx\n", pmap, (uint64_t)addr, (uint64_t)tte);
	#endif
	if ((tte & (ARM_TTE_TYPE_MASK | ARM_TTE_VALID)) != (ARM_TTE_TYPE_TABLE | ARM_TTE_VALID))
		return (PT_ENTRY_NULL);

	ttp = &((tt_entry_t*) phystokv(tte & ARM_TTE_TABLE_MASK))[tt2_index(pmap, addr)];
	return ((tt_entry_t *)ttp);
#endif
}