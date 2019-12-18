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
struct page {int dummy; } ;
struct kvm_memslots {int dummy; } ;
struct kvm_io_bus {int dummy; } ;
struct kvm_coalesced_mmio_ring {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct kvm {int /*<<< orphan*/  vm_list; int /*<<< orphan*/  users_count; int /*<<< orphan*/  slots_lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  requests_lock; int /*<<< orphan*/  mmu_lock; TYPE_2__* mm; struct kvm* memslots; int /*<<< orphan*/  srcu; struct kvm** buses; TYPE_1__ mmu_notifier; struct kvm_coalesced_mmio_ring* coalesced_mmio_ring; int /*<<< orphan*/  irq_ack_notifier_list; int /*<<< orphan*/  mask_notifier_list; } ;
struct TYPE_6__ {TYPE_2__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  mm_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kvm* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct kvm*) ; 
 int KVM_NR_BUSES ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  hardware_disable_all () ; 
 int hardware_enable_all () ; 
 int init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm*) ; 
 struct kvm* kvm_arch_create_vm () ; 
 int /*<<< orphan*/  kvm_coalesced_mmio_init (struct kvm*) ; 
 int /*<<< orphan*/  kvm_eventfd_init (struct kvm*) ; 
 int /*<<< orphan*/  kvm_lock ; 
 int /*<<< orphan*/  kvm_mmu_notifier_ops ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mmu_notifier_register (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_list ; 

__attribute__((used)) static struct kvm *kvm_create_vm(void)
{
	int r = 0, i;
	struct kvm *kvm = kvm_arch_create_vm();
#ifdef KVM_COALESCED_MMIO_PAGE_OFFSET
	struct page *page;
#endif

	if (IS_ERR(kvm))
		goto out;

	r = hardware_enable_all();
	if (r)
		goto out_err_nodisable;

#ifdef CONFIG_HAVE_KVM_IRQCHIP
	INIT_HLIST_HEAD(&kvm->mask_notifier_list);
	INIT_HLIST_HEAD(&kvm->irq_ack_notifier_list);
#endif
	kvm->memslots = kzalloc(sizeof(struct kvm_memslots), GFP_KERNEL);
	if (!kvm->memslots) {
		kfree(kvm);
		return ERR_PTR(-ENOMEM);
	}

	r = init_srcu_struct(&kvm->srcu);
	if (r) {
		kfree(kvm->memslots);
		kfree(kvm);
		return ERR_PTR(r);
	}

	for (i = 0; i < KVM_NR_BUSES; i++) {
		kvm->buses[i] = kzalloc(sizeof(struct kvm_io_bus),
					GFP_KERNEL);
		if (!kvm->buses[i]) {
			cleanup_srcu_struct(&kvm->srcu);
			kfree(kvm->memslots);
			kfree(kvm);
			return ERR_PTR(-ENOMEM);
		}
	}

#ifdef KVM_COALESCED_MMIO_PAGE_OFFSET
	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page) {
		for (i = 0; i < KVM_NR_BUSES; i++)
			kfree(kvm->buses[i]);
		cleanup_srcu_struct(&kvm->srcu);
		kfree(kvm->memslots);
		kfree(kvm);
		r = -ENOMEM;
		goto out_err;
	}
	kvm->coalesced_mmio_ring =
			(struct kvm_coalesced_mmio_ring *)page_address(page);
#endif

#if defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
	{
		kvm->mmu_notifier.ops = &kvm_mmu_notifier_ops;
		r = mmu_notifier_register(&kvm->mmu_notifier, current->mm);
		if (r) {
#ifdef KVM_COALESCED_MMIO_PAGE_OFFSET
			put_page(page);
#endif
			for (i = 0; i < KVM_NR_BUSES; i++)
				kfree(kvm->buses[i]);
			cleanup_srcu_struct(&kvm->srcu);
			kfree(kvm->memslots);
			kfree(kvm);
			goto out_err;
		}
	}
#endif

	kvm->mm = current->mm;
	atomic_inc(&kvm->mm->mm_count);
	spin_lock_init(&kvm->mmu_lock);
	spin_lock_init(&kvm->requests_lock);
	kvm_eventfd_init(kvm);
	mutex_init(&kvm->lock);
	mutex_init(&kvm->irq_lock);
	mutex_init(&kvm->slots_lock);
	atomic_set(&kvm->users_count, 1);
	spin_lock(&kvm_lock);
	list_add(&kvm->vm_list, &vm_list);
	spin_unlock(&kvm_lock);
#ifdef KVM_COALESCED_MMIO_PAGE_OFFSET
	kvm_coalesced_mmio_init(kvm);
#endif
out:
	return kvm;

out_err:
	hardware_disable_all();
out_err_nodisable:
	kfree(kvm);
	return ERR_PTR(r);
}