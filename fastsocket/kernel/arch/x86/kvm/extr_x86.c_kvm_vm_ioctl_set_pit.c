#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kvm_pit_state {TYPE_1__* channels; } ;
struct TYPE_6__ {TYPE_3__* vpit; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {TYPE_4__ pit_state; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_pit_load_count (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,struct kvm_pit_state*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vm_ioctl_set_pit(struct kvm *kvm, struct kvm_pit_state *ps)
{
	int r = 0;

	mutex_lock(&kvm->arch.vpit->pit_state.lock);
	memcpy(&kvm->arch.vpit->pit_state, ps, sizeof(struct kvm_pit_state));
	kvm_pit_load_count(kvm, 0, ps->channels[0].count, 0);
	mutex_unlock(&kvm->arch.vpit->pit_state.lock);
	return r;
}