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
typedef  union context {int dummy; } context ;
struct TYPE_4__ {int launched; } ;
struct kvm_vcpu {TYPE_2__* kvm; int /*<<< orphan*/  requests; TYPE_1__ arch; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* tramp_entry ) (union context*,union context*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  KVM_EXIT_FAIL_ENTRY ; 
 int /*<<< orphan*/  KVM_EXIT_INTR ; 
 int /*<<< orphan*/  KVM_REQ_KICK ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 union context* kvm_get_guest_context (struct kvm_vcpu*) ; 
 union context* kvm_get_host_context (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_guest_enter () ; 
 int /*<<< orphan*/  kvm_guest_exit () ; 
 int kvm_handle_exit (struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_resched (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_post_transition (struct kvm_vcpu*) ; 
 int kvm_vcpu_pre_transition (struct kvm_vcpu*) ; 
 TYPE_3__* kvm_vmm_info ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (union context*,union context*) ; 

__attribute__((used)) static int __vcpu_run(struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
{
	union context *host_ctx, *guest_ctx;
	int r, idx;

	idx = srcu_read_lock(&vcpu->kvm->srcu);

again:
	if (signal_pending(current)) {
		r = -EINTR;
		kvm_run->exit_reason = KVM_EXIT_INTR;
		goto out;
	}

	preempt_disable();
	local_irq_disable();

	/*Get host and guest context with guest address space.*/
	host_ctx = kvm_get_host_context(vcpu);
	guest_ctx = kvm_get_guest_context(vcpu);

	clear_bit(KVM_REQ_KICK, &vcpu->requests);

	r = kvm_vcpu_pre_transition(vcpu);
	if (r < 0)
		goto vcpu_run_fail;

	srcu_read_unlock(&vcpu->kvm->srcu, idx);
	kvm_guest_enter();

	/*
	 * Transition to the guest
	 */
	kvm_vmm_info->tramp_entry(host_ctx, guest_ctx);

	kvm_vcpu_post_transition(vcpu);

	vcpu->arch.launched = 1;
	set_bit(KVM_REQ_KICK, &vcpu->requests);
	local_irq_enable();

	/*
	 * We must have an instruction between local_irq_enable() and
	 * kvm_guest_exit(), so the timer interrupt isn't delayed by
	 * the interrupt shadow.  The stat.exits increment will do nicely.
	 * But we need to prevent reordering, hence this barrier():
	 */
	barrier();
	kvm_guest_exit();
	preempt_enable();

	idx = srcu_read_lock(&vcpu->kvm->srcu);

	r = kvm_handle_exit(kvm_run, vcpu);

	if (r > 0) {
		if (!need_resched())
			goto again;
	}

out:
	srcu_read_unlock(&vcpu->kvm->srcu, idx);
	if (r > 0) {
		kvm_resched(vcpu);
		idx = srcu_read_lock(&vcpu->kvm->srcu);
		goto again;
	}

	return r;

vcpu_run_fail:
	local_irq_enable();
	preempt_enable();
	kvm_run->exit_reason = KVM_EXIT_FAIL_ENTRY;
	goto out;
}