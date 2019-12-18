#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cause; } ;
struct l3_process {TYPE_3__* st; TYPE_1__ para; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int,struct l3_process*) ;} ;
struct TYPE_6__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int CC_RELEASE ; 
 int CONFIRM ; 
 int /*<<< orphan*/  NO_CAUSE ; 
 int /*<<< orphan*/  StopAllL3Timer (struct l3_process*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_l3_process (struct l3_process*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3_1tr6_rel_ack(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;

	dev_kfree_skb(skb);
	StopAllL3Timer(pc);
	newl3state(pc, 0);
	pc->para.cause = NO_CAUSE;
	pc->st->l3.l3l4(pc->st, CC_RELEASE | CONFIRM, pc);
	release_l3_process(pc);
}