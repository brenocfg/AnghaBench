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
struct vcpu_vmx {int invalid_state_emulation_result; } ;
struct kvm_vcpu {int dummy; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_DO_MMIO ; 
 int /*<<< orphan*/  current ; 
 int emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guest_state_valid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_report_emulation_failure (struct kvm_vcpu*,char*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static void handle_invalid_guest_state(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	enum emulation_result err = EMULATE_DONE;

	local_irq_enable();
	preempt_enable();

	while (!guest_state_valid(vcpu)) {
		err = emulate_instruction(vcpu, 0);

		if (err == EMULATE_DO_MMIO)
			break;

		if (err != EMULATE_DONE) {
			kvm_report_emulation_failure(vcpu, "emulation failure");
			break;
		}

		if (signal_pending(current))
			break;
		if (need_resched())
			schedule();
	}

	preempt_disable();
	local_irq_disable();

	vmx->invalid_state_emulation_result = err;
}