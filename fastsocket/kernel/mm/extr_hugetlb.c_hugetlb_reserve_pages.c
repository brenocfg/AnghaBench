#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; } ;
struct resv_map {int dummy; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 long ENOSPC ; 
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
 int VM_MAYSHARE ; 
 int VM_NORESERVE ; 
 struct hstate* hstate_inode (struct inode*) ; 
 scalar_t__ hugepage_subpool_get_pages (struct hugepage_subpool*,long) ; 
 int /*<<< orphan*/  hugepage_subpool_put_pages (struct hugepage_subpool*,long) ; 
 long hugetlb_acct_memory (struct hstate*,long) ; 
 int /*<<< orphan*/  region_add (int /*<<< orphan*/ *,long,long) ; 
 long region_chg (int /*<<< orphan*/ *,long,long) ; 
 struct resv_map* resv_map_alloc () ; 
 int /*<<< orphan*/  resv_map_put (struct vm_area_struct*) ; 
 int /*<<< orphan*/  set_vma_resv_flags (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_vma_resv_map (struct vm_area_struct*,struct resv_map*) ; 
 struct hugepage_subpool* subpool_inode (struct inode*) ; 

int hugetlb_reserve_pages(struct inode *inode,
					long from, long to,
					struct vm_area_struct *vma,
					int acctflag)
{
	long ret, chg;
	struct hstate *h = hstate_inode(inode);
	struct hugepage_subpool *spool = subpool_inode(inode);

	/*
	 * Only apply hugepage reservation if asked. At fault time, an
	 * attempt will be made for VM_NORESERVE to allocate a page
	 * without using reserves
	 */
	if (acctflag & VM_NORESERVE)
		return 0;

	/*
	 * Shared mappings base their reservation on the number of pages that
	 * are already allocated on behalf of the file. Private mappings need
	 * to reserve the full area even if read-only as mprotect() may be
	 * called to make the mapping read-write. Assume !vma is a shm mapping
	 */
	if (!vma || vma->vm_flags & VM_MAYSHARE)
		chg = region_chg(&inode->i_mapping->private_list, from, to);
	else {
		struct resv_map *resv_map = resv_map_alloc();
		if (!resv_map)
			return -ENOMEM;

		chg = to - from;

		set_vma_resv_map(vma, resv_map);
		set_vma_resv_flags(vma, HPAGE_RESV_OWNER);
	}

	if (chg < 0) {
		ret = chg;
		goto out_err;
	}

	/* There must be enough pages in the subpool for the mapping */
	if (hugepage_subpool_get_pages(spool, chg)) {
		ret = -ENOSPC;
		goto out_err;
	}

	/*
	 * Check enough hugepages are available for the reservation.
	 * Hand the pages back to the subpool if there are not
	 */
	ret = hugetlb_acct_memory(h, chg);
	if (ret < 0) {
		hugepage_subpool_put_pages(spool, chg);
		goto out_err;
	}

	/*
	 * Account for the reservations made. Shared mappings record regions
	 * that have reservations as they are shared by multiple VMAs.
	 * When the last VMA disappears, the region map says how much
	 * the reservation was and the page cache tells how much of
	 * the reservation was consumed. Private mappings are per-VMA and
	 * only the consumed reservations are tracked. When the VMA
	 * disappears, the original reservation is the VMA size and the
	 * consumed reservations are stored in the map. Hence, nothing
	 * else has to be done for private mappings here
	 */
	if (!vma || vma->vm_flags & VM_MAYSHARE)
		region_add(&inode->i_mapping->private_list, from, to);
	return 0;
out_err:
	if (vma)
		resv_map_put(vma);
	return ret;
}