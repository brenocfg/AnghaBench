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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vcpu_svm {TYPE_2__* vmcb; int /*<<< orphan*/  vcpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  insn_len; int /*<<< orphan*/  insn_bytes; int /*<<< orphan*/  exit_info_1; int /*<<< orphan*/  exit_info_2; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 scalar_t__ kvm_event_needs_reinjection (int /*<<< orphan*/ *) ; 
 int kvm_mmu_page_fault (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_unprotect_page_virt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npt_enabled ; 
 int /*<<< orphan*/  trace_kvm_page_fault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pf_interception(struct vcpu_svm *svm)
{
	u64 fault_address;
	u32 error_code;

	fault_address  = svm->vmcb->control.exit_info_2;
	error_code = svm->vmcb->control.exit_info_1;

	trace_kvm_page_fault(fault_address, error_code);
	if (!npt_enabled && kvm_event_needs_reinjection(&svm->vcpu))
		kvm_mmu_unprotect_page_virt(&svm->vcpu, fault_address);
	return kvm_mmu_page_fault(&svm->vcpu, fault_address, error_code,
				  svm->vmcb->control.insn_bytes,
				  svm->vmcb->control.insn_len);
}