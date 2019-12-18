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
struct TYPE_2__ {unsigned int eip_orig; } ;
struct x86_emulate_ctxt {scalar_t__ cs_base; TYPE_1__ decode; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int X86EMUL_UNHANDLEABLE ; 
 int do_fetch_insn_byte (struct x86_emulate_ctxt*,struct x86_emulate_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_insn_fetch(struct x86_emulate_ctxt *ctxt,
			 struct x86_emulate_ops *ops,
			 unsigned long eip, void *dest, unsigned size)
{
	int rc;

	/* x86 instructions are limited to 15 bytes. */
	if (eip + size - ctxt->decode.eip_orig > 15)
		return X86EMUL_UNHANDLEABLE;
	eip += ctxt->cs_base;
	while (size--) {
		rc = do_fetch_insn_byte(ctxt, ops, eip++, dest++);
		if (rc != X86EMUL_CONTINUE)
			return rc;
	}
	return X86EMUL_CONTINUE;
}