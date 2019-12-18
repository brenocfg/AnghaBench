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
struct x86_emulate_ctxt {scalar_t__ mode; int /*<<< orphan*/  vcpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_dr ) (int /*<<< orphan*/ ,int,unsigned long,int*) ;} ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 scalar_t__ X86EMUL_MODE_PROT64 ; 
 int X86EMUL_UNHANDLEABLE ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,unsigned long,int*) ; 

int emulator_set_dr(struct x86_emulate_ctxt *ctxt, int dr, unsigned long value)
{
	unsigned long mask = (ctxt->mode == X86EMUL_MODE_PROT64) ? ~0ULL : ~0U;
	int exception;

	if (!kvm_x86_ops->set_dr)
		return X86EMUL_UNHANDLEABLE;

	kvm_x86_ops->set_dr(ctxt->vcpu, dr, value & mask, &exception);
	if (exception) {
		/* FIXME: better handling */
		return X86EMUL_UNHANDLEABLE;
	}
	return X86EMUL_CONTINUE;
}