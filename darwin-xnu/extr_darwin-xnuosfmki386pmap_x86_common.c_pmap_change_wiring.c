#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/  wired_mem; } ;
struct TYPE_11__ {int wired_count; } ;
struct TYPE_12__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (int,int*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PTE_WIRED ; 
 int /*<<< orphan*/ * PT_ENTRY_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ iswired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_ledger_credit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_ledger_debit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pte (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_update_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ task_ledgers ; 

void
pmap_change_wiring(
	pmap_t		map,
	vm_map_offset_t	vaddr,
	boolean_t	wired)
{
	pt_entry_t	*pte;

	PMAP_LOCK(map);

	if ((pte = pmap_pte(map, vaddr)) == PT_ENTRY_NULL)
		panic("pmap_change_wiring(%p,0x%llx,%d): pte missing",
		      map, vaddr, wired);

	if (wired && !iswired(*pte)) {
		/*
		 * wiring down mapping
		 */
		pmap_ledger_credit(map, task_ledgers.wired_mem, PAGE_SIZE);
		OSAddAtomic(+1,  &map->stats.wired_count);
		pmap_update_pte(pte, 0, PTE_WIRED);
	}
	else if (!wired && iswired(*pte)) {
		/*
		 * unwiring mapping
		 */
		assert(map->stats.wired_count >= 1);
		OSAddAtomic(-1,  &map->stats.wired_count);
		pmap_ledger_debit(map, task_ledgers.wired_mem, PAGE_SIZE);
		pmap_update_pte(pte, PTE_WIRED, 0);
	}

	PMAP_UNLOCK(map);
}