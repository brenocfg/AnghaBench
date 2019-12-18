#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  mmio_exits; } ;
struct TYPE_10__ {int (* page_fault ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_5__ mmu; } ;
struct kvm_vcpu {TYPE_4__* run; TYPE_2__ stat; TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;
struct TYPE_8__ {int /*<<< orphan*/  ndata; int /*<<< orphan*/  suberror; } ;
struct TYPE_9__ {TYPE_3__ internal; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  EMULATE_DONE 130 
#define  EMULATE_DO_MMIO 129 
#define  EMULATE_FAIL 128 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  KVM_INTERNAL_ERROR_EMULATION ; 
 int mmu_topup_memory_caches (struct kvm_vcpu*) ; 
 int stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int x86_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

int kvm_mmu_page_fault(struct kvm_vcpu *vcpu, gva_t cr2, u32 error_code,
		       void *insn, int insn_len)
{
	int r;
	enum emulation_result er;

	r = vcpu->arch.mmu.page_fault(vcpu, cr2, error_code);
	if (r < 0)
		goto out;

	if (!r) {
		r = 1;
		goto out;
	}

	r = mmu_topup_memory_caches(vcpu);
	if (r)
		goto out;

	er = x86_emulate_instruction(vcpu, cr2, 0, insn, insn_len);

	switch (er) {
	case EMULATE_DONE:
		return 1;
	case EMULATE_DO_MMIO:
		++vcpu->stat.mmio_exits;
		return 0;
	case EMULATE_FAIL:
		vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->internal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->internal.ndata = 0;
		return 0;
	default:
		BUG();
	}
out:
	return r;
}