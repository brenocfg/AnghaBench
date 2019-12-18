#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_map_address_t ;
typedef  int pt_entry_t ;
typedef  TYPE_3__* pmap_t ;
struct TYPE_20__ {TYPE_1__* pt_cnt; } ;
struct TYPE_19__ {int /*<<< orphan*/  wired_mem; } ;
struct TYPE_17__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_18__ {TYPE_2__ stats; } ;
struct TYPE_16__ {int /*<<< orphan*/  wiredcnt; } ;
typedef  int /*<<< orphan*/  SInt32 ;
typedef  int /*<<< orphan*/  SInt16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_PTE_IS_COMPRESSED (int) ; 
 int ARM_PTE_TYPE_FAULT ; 
 int ARM_PTE_WIRED ; 
 size_t ARM_PT_DESC_INDEX (int*) ; 
 int /*<<< orphan*/  ISB_SY ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic16 (int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_TRACE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PMAP_UPDATE_TLBS (TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  PMAP__TTE ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (TYPE_3__*) ; 
 int /*<<< orphan*/  WRITE_PTE (int*,int) ; 
 int /*<<< orphan*/  WRITE_PTE_STRONG (int*,int) ; 
 int /*<<< orphan*/  __builtin_arm_isb (int /*<<< orphan*/ ) ; 
 TYPE_3__* kernel_pmap ; 
 int /*<<< orphan*/  pmap_ledger_credit (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_ledger_debit (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* ptep_get_ptd (int*) ; 
 TYPE_5__ task_ledgers ; 

__attribute__((used)) static inline void pmap_enter_pte(pmap_t pmap, pt_entry_t *pte_p, pt_entry_t pte, vm_map_address_t v)
{
	if (pmap != kernel_pmap && ((pte & ARM_PTE_WIRED) != (*pte_p & ARM_PTE_WIRED)))
	{
		SInt16	*ptd_wiredcnt_ptr = (SInt16 *)&(ptep_get_ptd(pte_p)->pt_cnt[ARM_PT_DESC_INDEX(pte_p)].wiredcnt);
		if (pte & ARM_PTE_WIRED) {
			OSAddAtomic16(1, ptd_wiredcnt_ptr);
			pmap_ledger_credit(pmap, task_ledgers.wired_mem, PAGE_SIZE);
			OSAddAtomic(1, (SInt32 *) &pmap->stats.wired_count);
		} else {
			OSAddAtomic16(-1, ptd_wiredcnt_ptr);
			pmap_ledger_debit(pmap, task_ledgers.wired_mem, PAGE_SIZE);
			OSAddAtomic(-1, (SInt32 *) &pmap->stats.wired_count);
		}
	}
	if (*pte_p != ARM_PTE_TYPE_FAULT &&
	    !ARM_PTE_IS_COMPRESSED(*pte_p)) {
		WRITE_PTE_STRONG(pte_p, pte);
		PMAP_UPDATE_TLBS(pmap, v, v + PAGE_SIZE);
	} else {
		WRITE_PTE(pte_p, pte);
		__builtin_arm_isb(ISB_SY);
	}

	PMAP_TRACE(3, PMAP_CODE(PMAP__TTE), VM_KERNEL_ADDRHIDE(pmap), VM_KERNEL_ADDRHIDE(v), VM_KERNEL_ADDRHIDE(v + PAGE_SIZE), pte);
}