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
struct TYPE_2__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  val; } ;
struct decode_cache {TYPE_1__ dst; } ;
struct x86_emulate_ctxt {struct decode_cache decode; } ;

/* Variables and functions */
 int emulate_pop (struct x86_emulate_ctxt*,struct x86_emulate_ops*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int emulate_grp1a(struct x86_emulate_ctxt *ctxt,
				struct x86_emulate_ops *ops)
{
	struct decode_cache *c = &ctxt->decode;

	return emulate_pop(ctxt, ops, &c->dst.val, c->dst.bytes);
}