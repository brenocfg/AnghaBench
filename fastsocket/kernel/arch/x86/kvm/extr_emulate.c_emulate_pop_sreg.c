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
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ops {int dummy; } ;
struct decode_cache {int /*<<< orphan*/  op_bytes; } ;
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; struct decode_cache decode; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int emulate_pop (struct x86_emulate_ctxt*,struct x86_emulate_ops*,unsigned long*,int /*<<< orphan*/ ) ; 
 int kvm_load_segment_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int emulate_pop_sreg(struct x86_emulate_ctxt *ctxt,
			     struct x86_emulate_ops *ops, int seg)
{
	struct decode_cache *c = &ctxt->decode;
	unsigned long selector;
	int rc;

	rc = emulate_pop(ctxt, ops, &selector, c->op_bytes);
	if (rc != X86EMUL_CONTINUE)
		return rc;

	rc = kvm_load_segment_descriptor(ctxt->vcpu, (u16)selector, seg);
	return rc;
}