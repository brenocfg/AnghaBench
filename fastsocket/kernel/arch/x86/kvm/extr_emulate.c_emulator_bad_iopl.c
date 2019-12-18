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
struct x86_emulate_ctxt {scalar_t__ mode; int eflags; int /*<<< orphan*/  vcpu; } ;
struct TYPE_2__ {int (* get_cpl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IOPL_SHIFT ; 
 scalar_t__ X86EMUL_MODE_REAL ; 
 scalar_t__ X86EMUL_MODE_VM86 ; 
 int X86_EFLAGS_IOPL ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool emulator_bad_iopl(struct x86_emulate_ctxt *ctxt)
{
	int iopl;
	if (ctxt->mode == X86EMUL_MODE_REAL)
		return false;
	if (ctxt->mode == X86EMUL_MODE_VM86)
		return true;
	iopl = (ctxt->eflags & X86_EFLAGS_IOPL) >> IOPL_SHIFT;
	return kvm_x86_ops->get_cpl(ctxt->vcpu) > iopl;
}