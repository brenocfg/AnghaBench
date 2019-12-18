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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ops {int (* cmpxchg_emulated ) (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* write_emulated ) (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int type; int /*<<< orphan*/  bytes; int /*<<< orphan*/  val; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  orig_val; } ;
struct decode_cache {TYPE_1__ dst; int /*<<< orphan*/  lock_prefix; } ;
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; struct decode_cache decode; } ;

/* Variables and functions */
#define  OP_MEM 130 
#define  OP_NONE 129 
#define  OP_REG 128 
 int X86EMUL_CONTINUE ; 
 int stub1 (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int writeback(struct x86_emulate_ctxt *ctxt,
			    struct x86_emulate_ops *ops)
{
	int rc;
	struct decode_cache *c = &ctxt->decode;

	switch (c->dst.type) {
	case OP_REG:
		/* The 4-byte case *is* correct:
		 * in 64-bit mode we zero-extend.
		 */
		switch (c->dst.bytes) {
		case 1:
			*(u8 *)c->dst.ptr = (u8)c->dst.val;
			break;
		case 2:
			*(u16 *)c->dst.ptr = (u16)c->dst.val;
			break;
		case 4:
			*c->dst.ptr = (u32)c->dst.val;
			break;	/* 64b: zero-ext */
		case 8:
			*c->dst.ptr = c->dst.val;
			break;
		}
		break;
	case OP_MEM:
		if (c->lock_prefix)
			rc = ops->cmpxchg_emulated(
					(unsigned long)c->dst.ptr,
					&c->dst.orig_val,
					&c->dst.val,
					c->dst.bytes,
					ctxt->vcpu);
		else
			rc = ops->write_emulated(
					(unsigned long)c->dst.ptr,
					&c->dst.val,
					c->dst.bytes,
					ctxt->vcpu);
		if (rc != 0)
			return rc;
		break;
	case OP_NONE:
		/* no writeback */
		break;
	default:
		break;
	}
	return X86EMUL_CONTINUE;
}