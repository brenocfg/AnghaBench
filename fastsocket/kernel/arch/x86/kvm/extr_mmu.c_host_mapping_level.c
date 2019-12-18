#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  int /*<<< orphan*/  gfn_t ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned long KVM_HPAGE_SIZE (int) ; 
 int KVM_NR_PAGE_SIZES ; 
 unsigned long PAGE_SIZE ; 
 int PT_PAGE_TABLE_LEVEL ; 
 scalar_t__ PageTransCompound (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 unsigned long gfn_to_hva (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hva_to_pfn (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  is_error_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 int /*<<< orphan*/  kvm_is_mmio_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 unsigned long vma_kernel_pagesize (struct vm_area_struct*) ; 

__attribute__((used)) static int host_mapping_level(struct kvm *kvm, gfn_t gfn)
{
	unsigned long page_size = PAGE_SIZE;
	struct vm_area_struct *vma;
	unsigned long addr;
	int i, ret = 0;

	addr = gfn_to_hva(kvm, gfn);
	if (kvm_is_error_hva(addr))
		return PT_PAGE_TABLE_LEVEL;

	down_read(&current->mm->mmap_sem);
	vma = find_vma(current->mm, addr);
	if (!vma)
		goto out;

	page_size = vma_kernel_pagesize(vma);

out:
	up_read(&current->mm->mmap_sem);

	/* check for transparent hugepages */
	if (page_size == PAGE_SIZE) {
		pfn_t pfn = hva_to_pfn(kvm, addr);

		if (!is_error_pfn(pfn) && !kvm_is_mmio_pfn(pfn) &&
		    PageTransCompound(pfn_to_page(pfn)))
			page_size = KVM_HPAGE_SIZE(2);
		kvm_release_pfn_clean(pfn);
	}

	for (i = PT_PAGE_TABLE_LEVEL;
	     i < (PT_PAGE_TABLE_LEVEL + KVM_NR_PAGE_SIZES); ++i) {
		if (page_size >= KVM_HPAGE_SIZE(i))
			ret = i;
		else
			break;
	}

	return ret;
}