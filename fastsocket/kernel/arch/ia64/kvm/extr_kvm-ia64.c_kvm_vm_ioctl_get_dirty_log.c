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
struct kvm_memory_slot {int /*<<< orphan*/  dirty_bitmap; } ;
struct kvm_dirty_log {size_t slot; } ;
struct TYPE_4__ {int /*<<< orphan*/  dirty_log_lock; } ;
struct kvm {TYPE_2__ arch; int /*<<< orphan*/  slots_lock; TYPE_1__* memslots; } ;
struct TYPE_3__ {struct kvm_memory_slot* memslots; } ;

/* Variables and functions */
 unsigned long kvm_dirty_bitmap_bytes (struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 int kvm_get_dirty_log (struct kvm*,struct kvm_dirty_log*,int*) ; 
 int kvm_ia64_sync_dirty_log (struct kvm*,struct kvm_dirty_log*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvm_vm_ioctl_get_dirty_log(struct kvm *kvm,
		struct kvm_dirty_log *log)
{
	int r;
	unsigned long n;
	struct kvm_memory_slot *memslot;
	int is_dirty = 0;

	mutex_lock(&kvm->slots_lock);
	spin_lock(&kvm->arch.dirty_log_lock);

	r = kvm_ia64_sync_dirty_log(kvm, log);
	if (r)
		goto out;

	r = kvm_get_dirty_log(kvm, log, &is_dirty);
	if (r)
		goto out;

	/* If nothing is dirty, don't bother messing with page tables. */
	if (is_dirty) {
		kvm_flush_remote_tlbs(kvm);
		memslot = &kvm->memslots->memslots[log->slot];
		n = kvm_dirty_bitmap_bytes(memslot);
		memset(memslot->dirty_bitmap, 0, n);
	}
	r = 0;
out:
	mutex_unlock(&kvm->slots_lock);
	spin_unlock(&kvm->arch.dirty_log_lock);
	return r;
}