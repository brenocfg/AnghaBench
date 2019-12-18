#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int tt_entry_t ;
typedef  scalar_t__ pt_entry_t ;
typedef  scalar_t__ ppnum_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int addr64_t ;
struct TYPE_9__ {int min; int max; } ;

/* Variables and functions */
 int ARM_PGMASK ; 
 scalar_t__ ARM_PTE_IS_COMPRESSED (scalar_t__) ; 
 int ARM_PTE_MASK ; 
 int ARM_TTE_BLOCK_L2_MASK ; 
 int ARM_TTE_BLOCK_SUPER ; 
 int ARM_TTE_TABLE_MASK ; 
 int ARM_TTE_TYPE_BLOCK ; 
 int ARM_TTE_TYPE_MASK ; 
 int ARM_TTE_TYPE_TABLE ; 
 int ARM_TTE_VALID ; 
 int ARM_TT_L1_BLOCK_OFFMASK ; 
 int ARM_TT_L1_SUPER_OFFMASK ; 
 int ARM_TT_L2_OFFMASK ; 
 int ARM_TT_L3_OFFMASK ; 
 scalar_t__ atop (int) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,int,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ phystokv (int) ; 
 int* pmap_tt1e (TYPE_1__*,int) ; 
 int* pmap_tt2e (TYPE_1__*,int) ; 
 int* pmap_tte (TYPE_1__*,int) ; 
 int pte_to_pa (scalar_t__) ; 
 int ptenum (int) ; 
 int sectte_to_pa (int) ; 
 int suptte_to_pa (int) ; 
 size_t tt2_index (TYPE_1__*,int) ; 
 size_t tt3_index (TYPE_1__*,int) ; 
 scalar_t__ ttetokv (int) ; 

ppnum_t
pmap_vtophys(
	pmap_t pmap,
	addr64_t va)
{
	if ((va < pmap->min) || (va >= pmap->max)) {
		return 0;
	}

#if	(__ARM_VMSA__ == 7)
	tt_entry_t     *tte_p, tte;
	pt_entry_t     *pte_p;
	ppnum_t         ppn;

	tte_p = pmap_tte(pmap, va);
	if (tte_p == (tt_entry_t *) NULL)
		return (ppnum_t) 0;

	tte = *tte_p;
	if ((tte & ARM_TTE_TYPE_MASK) == ARM_TTE_TYPE_TABLE) {
		pte_p = (pt_entry_t *) ttetokv(tte) + ptenum(va);
		ppn = (ppnum_t) atop(pte_to_pa(*pte_p) | (va & ARM_PGMASK));
#if DEVELOPMENT || DEBUG
		if (ppn != 0 &&
		    ARM_PTE_IS_COMPRESSED(*pte_p)) {
			panic("pmap_vtophys(%p,0x%llx): compressed pte_p=%p 0x%llx with ppn=0x%x\n",
			      pmap, va, pte_p, (uint64_t) (*pte_p), ppn);
		}
#endif /* DEVELOPMENT || DEBUG */
	} else if ((tte & ARM_TTE_TYPE_MASK) == ARM_TTE_TYPE_BLOCK)
		if ((tte & ARM_TTE_BLOCK_SUPER) == ARM_TTE_BLOCK_SUPER)
			ppn = (ppnum_t) atop(suptte_to_pa(tte) | (va & ARM_TT_L1_SUPER_OFFMASK));
		else
			ppn = (ppnum_t) atop(sectte_to_pa(tte) | (va & ARM_TT_L1_BLOCK_OFFMASK));
	else
		ppn = 0;
#else
	tt_entry_t		*ttp;
	tt_entry_t		tte;
	ppnum_t			ppn=0;

	/* Level 0 currently unused */

#if __ARM64_TWO_LEVEL_PMAP__
	/* We have no L1 entry; go straight to the L2 entry */
	ttp = pmap_tt2e(pmap, va);
	tte = *ttp;
#else
	/* Get first-level (1GB) entry */
	ttp = pmap_tt1e(pmap, va);
	tte = *ttp;
	if ((tte & (ARM_TTE_TYPE_MASK | ARM_TTE_VALID)) != (ARM_TTE_TYPE_TABLE | ARM_TTE_VALID))
		return (ppn);

	tte = ((tt_entry_t*) phystokv(tte & ARM_TTE_TABLE_MASK))[tt2_index(pmap, va)];
#endif
	if ((tte & ARM_TTE_VALID) != (ARM_TTE_VALID))
		return (ppn);

	if ((tte & ARM_TTE_TYPE_MASK) == ARM_TTE_TYPE_BLOCK) {
		ppn = (ppnum_t) atop((tte & ARM_TTE_BLOCK_L2_MASK)| (va & ARM_TT_L2_OFFMASK));
		return(ppn);
	}
	tte = ((tt_entry_t*) phystokv(tte & ARM_TTE_TABLE_MASK))[tt3_index(pmap, va)];
	ppn = (ppnum_t) atop((tte & ARM_PTE_MASK)| (va & ARM_TT_L3_OFFMASK));
#endif

	return ppn;
}