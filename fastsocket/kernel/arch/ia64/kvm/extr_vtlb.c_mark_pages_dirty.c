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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  dirty_log_lock_pa; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 scalar_t__ KVM_MEM_DIRTY_LOG_BASE ; 
 int PAGE_SHIFT ; 
 int _PAGE_PPN_MASK ; 
 int /*<<< orphan*/ * __kvm_va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,void*) ; 
 int /*<<< orphan*/  test_bit (int,void*) ; 
 int /*<<< orphan*/  vmm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmm_spin_unlock (int /*<<< orphan*/ *) ; 

void mark_pages_dirty(struct kvm_vcpu *v, u64 pte, u64 ps)
{
	u64 i, dirty_pages = 1;
	u64 base_gfn = (pte&_PAGE_PPN_MASK) >> PAGE_SHIFT;
	spinlock_t *lock = __kvm_va(v->arch.dirty_log_lock_pa);
	void *dirty_bitmap = (void *)KVM_MEM_DIRTY_LOG_BASE;

	dirty_pages <<= ps <= PAGE_SHIFT ? 0 : ps - PAGE_SHIFT;

	vmm_spin_lock(lock);
	for (i = 0; i < dirty_pages; i++) {
		/* avoid RMW */
		if (!test_bit(base_gfn + i, dirty_bitmap))
			set_bit(base_gfn + i , dirty_bitmap);
	}
	vmm_spin_unlock(lock);
}