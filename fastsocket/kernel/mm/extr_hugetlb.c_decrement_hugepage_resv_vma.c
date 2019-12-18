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
struct vm_area_struct {int vm_flags; } ;
struct hstate {int /*<<< orphan*/  resv_huge_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
 int VM_MAYSHARE ; 
 int VM_NORESERVE ; 
 scalar_t__ is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decrement_hugepage_resv_vma(struct hstate *h,
			struct vm_area_struct *vma)
{
	if (vma->vm_flags & VM_NORESERVE)
		return;

	if (vma->vm_flags & VM_MAYSHARE) {
		/* Shared mappings always use reserves */
		h->resv_huge_pages--;
	} else if (is_vma_resv_set(vma, HPAGE_RESV_OWNER)) {
		/*
		 * Only the process that called mmap() has reserves for
		 * private mappings.
		 */
		h->resv_huge_pages--;
	}
}