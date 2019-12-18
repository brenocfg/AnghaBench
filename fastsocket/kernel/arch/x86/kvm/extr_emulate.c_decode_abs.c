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
struct x86_emulate_ops {int dummy; } ;
struct decode_cache {int ad_bytes; int /*<<< orphan*/  eip; void* modrm_ea; } ;
struct x86_emulate_ctxt {struct decode_cache decode; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 void* insn_fetch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static int decode_abs(struct x86_emulate_ctxt *ctxt,
		      struct x86_emulate_ops *ops)
{
	struct decode_cache *c = &ctxt->decode;
	int rc = X86EMUL_CONTINUE;

	switch (c->ad_bytes) {
	case 2:
		c->modrm_ea = insn_fetch(u16, 2, c->eip);
		break;
	case 4:
		c->modrm_ea = insn_fetch(u32, 4, c->eip);
		break;
	case 8:
		c->modrm_ea = insn_fetch(u64, 8, c->eip);
		break;
	}
done:
	return rc;
}