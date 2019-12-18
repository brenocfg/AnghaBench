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
struct kvm_assigned_msix_entry {scalar_t__ entry; scalar_t__ gsi; int /*<<< orphan*/  assigned_dev_id; } ;
struct kvm_assigned_dev_kernel {int entries_nr; TYPE_3__* host_msix_entries; TYPE_2__* guest_msix_entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  assigned_dev_head; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_1__ arch; } ;
struct TYPE_6__ {scalar_t__ entry; } ;
struct TYPE_5__ {scalar_t__ vector; scalar_t__ entry; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 struct kvm_assigned_dev_kernel* kvm_find_assigned_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vm_ioctl_set_msix_entry(struct kvm *kvm,
				       struct kvm_assigned_msix_entry *entry)
{
	int r = 0, i;
	struct kvm_assigned_dev_kernel *adev;

	mutex_lock(&kvm->lock);

	adev = kvm_find_assigned_dev(&kvm->arch.assigned_dev_head,
				      entry->assigned_dev_id);

	if (!adev) {
		r = -EINVAL;
		goto msix_entry_out;
	}

	for (i = 0; i < adev->entries_nr; i++)
		if (adev->guest_msix_entries[i].vector == 0 ||
		    adev->guest_msix_entries[i].entry == entry->entry) {
			adev->guest_msix_entries[i].entry = entry->entry;
			adev->guest_msix_entries[i].vector = entry->gsi;
			adev->host_msix_entries[i].entry = entry->entry;
			break;
		}
	if (i == adev->entries_nr) {
		r = -ENOSPC;
		goto msix_entry_out;
	}

msix_entry_out:
	mutex_unlock(&kvm->lock);

	return r;
}