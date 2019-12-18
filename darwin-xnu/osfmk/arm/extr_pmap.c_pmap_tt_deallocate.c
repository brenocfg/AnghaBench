#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_17__ {struct TYPE_17__* next; } ;
typedef  TYPE_3__ tt_free_entry_t ;
typedef  int /*<<< orphan*/  tt_entry_t ;
struct TYPE_18__ {TYPE_2__* pt_cnt; TYPE_1__* pt_map; } ;
typedef  TYPE_4__ pt_desc_t ;
typedef  TYPE_5__* pmap_t ;
struct TYPE_19__ {int /*<<< orphan*/ * tt_entry_free; } ;
struct TYPE_16__ {scalar_t__ refcnt; } ;
struct TYPE_15__ {scalar_t__ va; } ;

/* Variables and functions */
 size_t ARM_PT_DESC_INDEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_MASK ; 
 unsigned int PAGE_RATIO ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_5__*) ; 
 unsigned int PMAP_TT_MAX_LEVEL ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  PMAP_ZINFO_PFREE (TYPE_5__*,scalar_t__) ; 
 scalar_t__ PT_DESC_REFCOUNT ; 
 int /*<<< orphan*/  inuse_kernel_ptepages_count ; 
 int /*<<< orphan*/  inuse_kernel_ttepages_count ; 
 int /*<<< orphan*/  inuse_user_ptepages_count ; 
 int /*<<< orphan*/  inuse_user_ttepages_count ; 
 TYPE_5__* kernel_pmap ; 
 int /*<<< orphan*/  ml_static_vtop (scalar_t__) ; 
 int /*<<< orphan*/  pa_index (int /*<<< orphan*/ ) ; 
 scalar_t__ pai_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  pmap_pages_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_tt_ledger_debit (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ptd_deallocate (TYPE_4__*) ; 
 TYPE_4__* ptep_get_ptd (scalar_t__) ; 

__attribute__((used)) static void
pmap_tt_deallocate(
	pmap_t pmap,
	tt_entry_t *ttp,
	unsigned int level)
{
	pt_desc_t *ptdp;
	unsigned pt_acc_cnt;
	unsigned i, max_pt_index = PAGE_RATIO;
	vm_offset_t	free_page=0;

	PMAP_LOCK(pmap);

	ptdp = ptep_get_ptd((vm_offset_t)ttp);

	ptdp->pt_map[ARM_PT_DESC_INDEX(ttp)].va = (vm_offset_t)-1;

	if ((level < PMAP_TT_MAX_LEVEL) && (ptdp->pt_cnt[ARM_PT_DESC_INDEX(ttp)].refcnt == PT_DESC_REFCOUNT))
		ptdp->pt_cnt[ARM_PT_DESC_INDEX(ttp)].refcnt = 0;

	if (ptdp->pt_cnt[ARM_PT_DESC_INDEX(ttp)].refcnt != 0)
		panic("pmap_tt_deallocate(): ptdp %p, count %d\n", ptdp, ptdp->pt_cnt[ARM_PT_DESC_INDEX(ttp)].refcnt);

	ptdp->pt_cnt[ARM_PT_DESC_INDEX(ttp)].refcnt = 0;

	for (i = 0, pt_acc_cnt = 0 ; i < max_pt_index ; i++)
		pt_acc_cnt += ptdp->pt_cnt[i].refcnt;

	if (pt_acc_cnt == 0) {
		tt_free_entry_t *tt_free_list = (tt_free_entry_t *)&pmap->tt_entry_free;
		unsigned pt_free_entry_cnt = 1;

		while (pt_free_entry_cnt < max_pt_index && tt_free_list) {
			tt_free_entry_t *tt_free_list_next;

			tt_free_list_next = tt_free_list->next;
			if ((((vm_offset_t)tt_free_list_next) - ((vm_offset_t)ttp & ~PAGE_MASK)) < PAGE_SIZE) {
				pt_free_entry_cnt++;
			}
			tt_free_list = tt_free_list_next;
		}
		if (pt_free_entry_cnt == max_pt_index) {
			tt_free_entry_t *tt_free_list_cur;

			free_page = (vm_offset_t)ttp & ~PAGE_MASK;
			tt_free_list = (tt_free_entry_t *)&pmap->tt_entry_free;
			tt_free_list_cur = (tt_free_entry_t *)&pmap->tt_entry_free;

			while (tt_free_list_cur) {
				tt_free_entry_t *tt_free_list_next;

				tt_free_list_next = tt_free_list_cur->next;
				if ((((vm_offset_t)tt_free_list_next) - free_page) < PAGE_SIZE) {
					tt_free_list->next = tt_free_list_next->next;
				} else {
					tt_free_list = tt_free_list_next;
				}
				tt_free_list_cur = tt_free_list_next;
			}
		} else {
			((tt_free_entry_t *)ttp)->next = (tt_free_entry_t *)pmap->tt_entry_free;
			pmap->tt_entry_free = ttp;
		}
	} else {
		((tt_free_entry_t *)ttp)->next = (tt_free_entry_t *)pmap->tt_entry_free;
		pmap->tt_entry_free = ttp;
	}

	PMAP_UNLOCK(pmap);

	if (free_page != 0) {

		ptd_deallocate(ptep_get_ptd((vm_offset_t)free_page));
		*(pt_desc_t **)pai_to_pvh(pa_index(ml_static_vtop(free_page))) = NULL;
		pmap_pages_free(ml_static_vtop(free_page), PAGE_SIZE);
		if (level < PMAP_TT_MAX_LEVEL)
			OSAddAtomic(-1, (pmap == kernel_pmap ? &inuse_kernel_ttepages_count : &inuse_user_ttepages_count));
		else
			OSAddAtomic(-1, (pmap == kernel_pmap ? &inuse_kernel_ptepages_count : &inuse_user_ptepages_count));
		PMAP_ZINFO_PFREE(pmap, PAGE_SIZE);
		pmap_tt_ledger_debit(pmap, PAGE_SIZE);
	}
}