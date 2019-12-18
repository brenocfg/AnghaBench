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
typedef  int u16 ;
struct decode_cache {int eip; int* regs; } ;
struct x86_emulate_ctxt {int mode; int eflags; int /*<<< orphan*/  vcpu; struct decode_cache decode; } ;
struct kvm_segment {int selector; int l; scalar_t__ db; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_msr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* set_segment ) (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EFLG_IF ; 
 int EFLG_RF ; 
 int EFLG_VM ; 
 int /*<<< orphan*/  MSR_IA32_SYSENTER_CS ; 
 int /*<<< orphan*/  MSR_IA32_SYSENTER_EIP ; 
 int /*<<< orphan*/  MSR_IA32_SYSENTER_ESP ; 
 int SELECTOR_RPL_MASK ; 
 size_t VCPU_REGS_RSP ; 
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 int X86EMUL_CONTINUE ; 
#define  X86EMUL_MODE_PROT32 129 
#define  X86EMUL_MODE_PROT64 128 
 int X86EMUL_MODE_REAL ; 
 int X86EMUL_PROPAGATE_FAULT ; 
 int X86EMUL_UNHANDLEABLE ; 
 scalar_t__ is_long_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_gp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  setup_syscalls_segments (struct x86_emulate_ctxt*,struct kvm_segment*,struct kvm_segment*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
emulate_sysenter(struct x86_emulate_ctxt *ctxt)
{
	struct decode_cache *c = &ctxt->decode;
	struct kvm_segment cs, ss;
	u64 msr_data;

	/* inject #GP if in real mode */
	if (ctxt->mode == X86EMUL_MODE_REAL) {
		kvm_inject_gp(ctxt->vcpu, 0);
		return X86EMUL_UNHANDLEABLE;
	}

	/* XXX sysenter/sysexit have not been tested in 64bit mode.
	* Therefore, we inject an #UD.
	*/
	if (ctxt->mode == X86EMUL_MODE_PROT64)
		return X86EMUL_UNHANDLEABLE;

	setup_syscalls_segments(ctxt, &cs, &ss);

	kvm_x86_ops->get_msr(ctxt->vcpu, MSR_IA32_SYSENTER_CS, &msr_data);
	switch (ctxt->mode) {
	case X86EMUL_MODE_PROT32:
		if ((msr_data & 0xfffc) == 0x0) {
			kvm_inject_gp(ctxt->vcpu, 0);
			return X86EMUL_PROPAGATE_FAULT;
		}
		break;
	case X86EMUL_MODE_PROT64:
		if (msr_data == 0x0) {
			kvm_inject_gp(ctxt->vcpu, 0);
			return X86EMUL_PROPAGATE_FAULT;
		}
		break;
	}

	ctxt->eflags &= ~(EFLG_VM | EFLG_IF | EFLG_RF);
	cs.selector = (u16)msr_data;
	cs.selector &= ~SELECTOR_RPL_MASK;
	ss.selector = cs.selector + 8;
	ss.selector &= ~SELECTOR_RPL_MASK;
	if (ctxt->mode == X86EMUL_MODE_PROT64
		|| is_long_mode(ctxt->vcpu)) {
		cs.db = 0;
		cs.l = 1;
	}

	kvm_x86_ops->set_segment(ctxt->vcpu, &cs, VCPU_SREG_CS);
	kvm_x86_ops->set_segment(ctxt->vcpu, &ss, VCPU_SREG_SS);

	kvm_x86_ops->get_msr(ctxt->vcpu, MSR_IA32_SYSENTER_EIP, &msr_data);
	c->eip = msr_data;

	kvm_x86_ops->get_msr(ctxt->vcpu, MSR_IA32_SYSENTER_ESP, &msr_data);
	c->regs[VCPU_REGS_RSP] = msr_data;

	return X86EMUL_CONTINUE;
}