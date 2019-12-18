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
struct TYPE_2__ {scalar_t__ tid; } ;
struct cryptocop_transform_ctx {struct cryptocop_transform_ctx* next; TYPE_1__ init; } ;
struct cryptocop_session {struct cryptocop_transform_ctx* tfrm_ctx; } ;
typedef  scalar_t__ cryptocop_tfrm_id ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static struct cryptocop_transform_ctx *get_transform_ctx(struct cryptocop_session *sess, cryptocop_tfrm_id tid)
{
	struct cryptocop_transform_ctx *tc = sess->tfrm_ctx;

	DEBUG(printk("get_transform_ctx, sess=0x%p, tid=%d\n", sess, tid));
	assert(sess != NULL);
	while (tc && tc->init.tid != tid){
		DEBUG(printk("tc=0x%p, tc->next=0x%p\n", tc, tc->next));
		tc = tc->next;
	}
	DEBUG(printk("get_transform_ctx, returning tc=0x%p\n", tc));
	return tc;
}