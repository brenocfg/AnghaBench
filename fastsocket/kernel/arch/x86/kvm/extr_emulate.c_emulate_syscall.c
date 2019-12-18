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
typedef  int u32 ;
typedef  void* u16 ;
struct x86_emulate_ops {int dummy; } ;
struct decode_cache {int* regs; int eip; } ;
struct x86_emulate_ctxt {scalar_t__ mode; int eflags; int /*<<< orphan*/  vcpu; struct decode_cache decode; } ;
struct kvm_segment {int l; scalar_t__ db; void* selector; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_msr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* set_segment ) (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EFER_SCE ; 
 int EFLG_IF ; 
 int EFLG_RF ; 
 int EFLG_VM ; 
 int /*<<< orphan*/  MSR_CSTAR ; 
 int /*<<< orphan*/  MSR_EFER ; 
 int /*<<< orphan*/  MSR_LSTAR ; 
 int /*<<< orphan*/  MSR_STAR ; 
 int /*<<< orphan*/  MSR_SYSCALL_MASK ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 size_t VCPU_REGS_R11 ; 
 size_t VCPU_REGS_RCX ; 
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 int X86EMUL_CONTINUE ; 
 scalar_t__ X86EMUL_MODE_PROT64 ; 
 scalar_t__ X86EMUL_MODE_REAL ; 
 scalar_t__ X86EMUL_MODE_VM86 ; 
 int X86EMUL_PROPAGATE_FAULT ; 
 int X86EMUL_UNHANDLEABLE ; 
 int /*<<< orphan*/  em_syscall_is_enabled (struct x86_emulate_ctxt*,struct x86_emulate_ops*) ; 
 scalar_t__ is_long_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  setup_syscalls_segments (struct x86_emulate_ctxt*,struct kvm_segment*,struct kvm_segment*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
emulate_syscall(struct x86_emulate_ctxt *ctxt, struct x86_emulate_ops *ops)
{
	struct decode_cache *c = &ctxt->decode;
	struct kvm_segment cs, ss;
	u64 msr_data;
	u64 efer;

	/* syscall is not available in real mode */
	if (ctxt->mode == X86EMUL_MODE_REAL || ctxt->mode == X86EMUL_MODE_VM86)
		return X86EMUL_UNHANDLEABLE;

	if (!(em_syscall_is_enabled(ctxt, ops))) {
		kvm_queue_exception(ctxt->vcpu, UD_VECTOR);
		return X86EMUL_PROPAGATE_FAULT;
	}

	setup_syscalls_segments(ctxt, &cs, &ss);

	kvm_x86_ops->get_msr(ctxt->vcpu, MSR_EFER, &efer);

	if (!(efer & EFER_SCE)) {
		kvm_queue_exception(ctxt->vcpu, UD_VECTOR);
		return X86EMUL_PROPAGATE_FAULT;
	}

	kvm_x86_ops->get_msr(ctxt->vcpu, MSR_STAR, &msr_data);
	msr_data >>= 32;
	cs.selector = (u16)(msr_data & 0xfffc);
	ss.selector = (u16)(msr_data + 8);

	if (is_long_mode(ctxt->vcpu)) {
		cs.db = 0;
		cs.l = 1;
	}
	kvm_x86_ops->set_segment(ctxt->vcpu, &cs, VCPU_SREG_CS);
	kvm_x86_ops->set_segment(ctxt->vcpu, &ss, VCPU_SREG_SS);

	c->regs[VCPU_REGS_RCX] = c->eip;
	if (is_long_mode(ctxt->vcpu)) {
#ifdef CONFIG_X86_64
		c->regs[VCPU_REGS_R11] = ctxt->eflags & ~EFLG_RF;

		kvm_x86_ops->get_msr(ctxt->vcpu,
			ctxt->mode == X86EMUL_MODE_PROT64 ?
			MSR_LSTAR : MSR_CSTAR, &msr_data);
		c->eip = msr_data;

		kvm_x86_ops->get_msr(ctxt->vcpu, MSR_SYSCALL_MASK, &msr_data);
		ctxt->eflags &= ~(msr_data | EFLG_RF);
#endif
	} else {
		/* legacy mode */
		kvm_x86_ops->get_msr(ctxt->vcpu, MSR_STAR, &msr_data);
		c->eip = (u32)msr_data;

		ctxt->eflags &= ~(EFLG_VM | EFLG_IF | EFLG_RF);
	}

	return X86EMUL_CONTINUE;
}