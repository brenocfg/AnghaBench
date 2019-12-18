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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct x86_emulate_ops {int (* read_emulated ) (unsigned long,int*,int,int /*<<< orphan*/ ) ;int (* cmpxchg_emulated ) (unsigned long,int*,int*,int,int /*<<< orphan*/ ) ;} ;
struct decode_cache {scalar_t__* regs; } ;
struct x86_emulate_ctxt {int /*<<< orphan*/  eflags; int /*<<< orphan*/  vcpu; struct decode_cache decode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFLG_ZF ; 
 size_t VCPU_REGS_RAX ; 
 size_t VCPU_REGS_RBX ; 
 size_t VCPU_REGS_RCX ; 
 size_t VCPU_REGS_RDX ; 
 int X86EMUL_CONTINUE ; 
 int stub1 (unsigned long,int*,int,int /*<<< orphan*/ ) ; 
 int stub2 (unsigned long,int*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int emulate_grp9(struct x86_emulate_ctxt *ctxt,
			       struct x86_emulate_ops *ops,
			       unsigned long memop)
{
	struct decode_cache *c = &ctxt->decode;
	u64 old, new;
	int rc;

	rc = ops->read_emulated(memop, &old, 8, ctxt->vcpu);
	if (rc != 0)
		return rc;

	if (((u32) (old >> 0) != (u32) c->regs[VCPU_REGS_RAX]) ||
	    ((u32) (old >> 32) != (u32) c->regs[VCPU_REGS_RDX])) {

		c->regs[VCPU_REGS_RAX] = (u32) (old >> 0);
		c->regs[VCPU_REGS_RDX] = (u32) (old >> 32);
		ctxt->eflags &= ~EFLG_ZF;

	} else {
		new = ((u64)c->regs[VCPU_REGS_RCX] << 32) |
		       (u32) c->regs[VCPU_REGS_RBX];

		rc = ops->cmpxchg_emulated(memop, &old, &new, 8, ctxt->vcpu);
		if (rc != 0)
			return rc;
		ctxt->eflags |= EFLG_ZF;
	}
	return X86EMUL_CONTINUE;
}