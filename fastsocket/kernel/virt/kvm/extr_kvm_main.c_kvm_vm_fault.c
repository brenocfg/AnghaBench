#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {struct page* page; int /*<<< orphan*/  pgoff; } ;
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct page {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;
struct TYPE_5__ {int /*<<< orphan*/  mm; } ;
struct TYPE_4__ {struct kvm* private_data; } ;

/* Variables and functions */
 int VM_FAULT_SIGBUS ; 
 TYPE_2__* current ; 
 int get_user_pages (TYPE_2__*,int /*<<< orphan*/ ,unsigned long,int,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 unsigned long gfn_to_hva (struct kvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int kvm_vm_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct page *page[1];
	unsigned long addr;
	int npages;
	gfn_t gfn = vmf->pgoff;
	struct kvm *kvm = vma->vm_file->private_data;

	addr = gfn_to_hva(kvm, gfn);
	if (kvm_is_error_hva(addr))
		return VM_FAULT_SIGBUS;

	npages = get_user_pages(current, current->mm, addr, 1, 1, 0, page,
				NULL);
	if (unlikely(npages != 1))
		return VM_FAULT_SIGBUS;

	vmf->page = page[0];
	return 0;
}