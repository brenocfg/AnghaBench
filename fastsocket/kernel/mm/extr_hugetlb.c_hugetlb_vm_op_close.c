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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct resv_map {int /*<<< orphan*/  regions; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  hugepage_subpool_put_pages (struct hugepage_subpool*,unsigned long) ; 
 int /*<<< orphan*/  hugetlb_acct_memory (struct hstate*,unsigned long) ; 
 unsigned long region_count (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  resv_map_put (struct vm_area_struct*) ; 
 struct hugepage_subpool* subpool_vma (struct vm_area_struct*) ; 
 unsigned long vma_hugecache_offset (struct hstate*,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 struct resv_map* vma_resv_map (struct vm_area_struct*) ; 

__attribute__((used)) static void hugetlb_vm_op_close(struct vm_area_struct *vma)
{
	struct hstate *h = hstate_vma(vma);
	struct resv_map *reservations = vma_resv_map(vma);
	struct hugepage_subpool *spool = subpool_vma(vma);
	unsigned long reserve;
	unsigned long start;
	unsigned long end;

	if (reservations) {
		start = vma_hugecache_offset(h, vma, vma->vm_start);
		end = vma_hugecache_offset(h, vma, vma->vm_end);

		reserve = (end - start) -
			region_count(&reservations->regions, start, end);
		resv_map_put(vma);

		if (reserve) {
			hugetlb_acct_memory(h, -reserve);
			hugepage_subpool_put_pages(spool, reserve);
		}
	}
}