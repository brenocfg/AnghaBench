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
struct TYPE_2__ {long val; } ;
struct decode_cache {int modrm_reg; long eip; TYPE_1__ src; int /*<<< orphan*/  dst; } ;
struct x86_emulate_ctxt {int /*<<< orphan*/  eflags; struct decode_cache decode; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int /*<<< orphan*/  emulate_1op (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emulate_push (struct x86_emulate_ctxt*) ; 

__attribute__((used)) static inline int emulate_grp45(struct x86_emulate_ctxt *ctxt,
			       struct x86_emulate_ops *ops)
{
	struct decode_cache *c = &ctxt->decode;

	switch (c->modrm_reg) {
	case 0:	/* inc */
		emulate_1op("inc", c->dst, ctxt->eflags);
		break;
	case 1:	/* dec */
		emulate_1op("dec", c->dst, ctxt->eflags);
		break;
	case 2: /* call near abs */ {
		long int old_eip;
		old_eip = c->eip;
		c->eip = c->src.val;
		c->src.val = old_eip;
		emulate_push(ctxt);
		break;
	}
	case 4: /* jmp abs */
		c->eip = c->src.val;
		break;
	case 6:	/* push */
		emulate_push(ctxt);
		break;
	}
	return X86EMUL_CONTINUE;
}