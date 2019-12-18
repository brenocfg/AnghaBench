#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {scalar_t__ pgoff; struct page* page; } ;
struct vm_area_struct {TYPE_3__* vm_file; } ;
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pio_data; } ;
struct kvm_vcpu {TYPE_2__* kvm; TYPE_1__ arch; int /*<<< orphan*/  run; } ;
struct TYPE_6__ {struct kvm_vcpu* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  coalesced_mmio_ring; } ;

/* Variables and functions */
 scalar_t__ KVM_COALESCED_MMIO_PAGE_OFFSET ; 
 scalar_t__ KVM_PIO_PAGE_OFFSET ; 
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_vcpu_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct kvm_vcpu *vcpu = vma->vm_file->private_data;
	struct page *page;

	if (vmf->pgoff == 0)
		page = virt_to_page(vcpu->run);
#ifdef CONFIG_X86
	else if (vmf->pgoff == KVM_PIO_PAGE_OFFSET)
		page = virt_to_page(vcpu->arch.pio_data);
#endif
#ifdef KVM_COALESCED_MMIO_PAGE_OFFSET
	else if (vmf->pgoff == KVM_COALESCED_MMIO_PAGE_OFFSET)
		page = virt_to_page(vcpu->kvm->coalesced_mmio_ring);
#endif
	else
		return VM_FAULT_SIGBUS;
	get_page(page);
	vmf->page = page;
	return 0;
}