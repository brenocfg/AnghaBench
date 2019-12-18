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
typedef  unsigned long u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ops {int dummy; } ;
struct decode_cache {unsigned long eip; int op_bytes; } ;
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; struct decode_cache decode; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int X86EMUL_CONTINUE ; 
 int emulate_pop (struct x86_emulate_ctxt*,struct x86_emulate_ops*,unsigned long*,int) ; 
 int kvm_load_segment_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emulate_ret_far(struct x86_emulate_ctxt *ctxt,
			   struct x86_emulate_ops *ops)
{
	struct decode_cache *c = &ctxt->decode;
	int rc;
	unsigned long cs;

	rc = emulate_pop(ctxt, ops, &c->eip, c->op_bytes);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	if (c->op_bytes == 4)
		c->eip = (u32)c->eip;
	rc = emulate_pop(ctxt, ops, &cs, c->op_bytes);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	rc = kvm_load_segment_descriptor(ctxt->vcpu, (u16)cs, VCPU_SREG_CS);
	return rc;
}