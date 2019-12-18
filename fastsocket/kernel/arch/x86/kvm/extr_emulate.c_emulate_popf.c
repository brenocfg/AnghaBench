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
struct x86_emulate_ops {int dummy; } ;
struct x86_emulate_ctxt {int eflags; int mode; int /*<<< orphan*/  vcpu; } ;
struct TYPE_2__ {int (* get_cpl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned long EFLG_AC ; 
 unsigned long EFLG_AF ; 
 unsigned long EFLG_CF ; 
 unsigned long EFLG_DF ; 
 unsigned long EFLG_ID ; 
 unsigned long EFLG_IF ; 
 unsigned long EFLG_IOPL ; 
 unsigned long EFLG_NT ; 
 unsigned long EFLG_OF ; 
 unsigned long EFLG_PF ; 
 unsigned long EFLG_RF ; 
 unsigned long EFLG_SF ; 
 unsigned long EFLG_TF ; 
 unsigned long EFLG_ZF ; 
 int IOPL_SHIFT ; 
 int X86EMUL_CONTINUE ; 
#define  X86EMUL_MODE_PROT16 131 
#define  X86EMUL_MODE_PROT32 130 
#define  X86EMUL_MODE_PROT64 129 
#define  X86EMUL_MODE_VM86 128 
 int X86EMUL_PROPAGATE_FAULT ; 
 int X86_EFLAGS_IOPL ; 
 int emulate_pop (struct x86_emulate_ctxt*,struct x86_emulate_ops*,unsigned long*,int) ; 
 int /*<<< orphan*/  kvm_inject_gp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emulate_popf(struct x86_emulate_ctxt *ctxt,
		       struct x86_emulate_ops *ops,
		       void *dest, int len)
{
	int rc;
	unsigned long val, change_mask;
	int iopl = (ctxt->eflags & X86_EFLAGS_IOPL) >> IOPL_SHIFT;
	int cpl = kvm_x86_ops->get_cpl(ctxt->vcpu);

	rc = emulate_pop(ctxt, ops, &val, len);
	if (rc != X86EMUL_CONTINUE)
		return rc;

	change_mask = EFLG_CF | EFLG_PF | EFLG_AF | EFLG_ZF | EFLG_SF | EFLG_OF
		| EFLG_TF | EFLG_DF | EFLG_NT | EFLG_RF | EFLG_AC | EFLG_ID;

	switch(ctxt->mode) {
	case X86EMUL_MODE_PROT64:
	case X86EMUL_MODE_PROT32:
	case X86EMUL_MODE_PROT16:
		if (cpl == 0)
			change_mask |= EFLG_IOPL;
		if (cpl <= iopl)
			change_mask |= EFLG_IF;
		break;
	case X86EMUL_MODE_VM86:
		if (iopl < 3) {
			kvm_inject_gp(ctxt->vcpu, 0);
			return X86EMUL_PROPAGATE_FAULT;
		}
		change_mask |= EFLG_IF;
		break;
	default: /* real mode */
		change_mask |= (EFLG_IOPL | EFLG_IF);
		break;
	}

	*(unsigned long *)dest =
		(ctxt->eflags & ~change_mask) | (val & change_mask);

	return rc;
}