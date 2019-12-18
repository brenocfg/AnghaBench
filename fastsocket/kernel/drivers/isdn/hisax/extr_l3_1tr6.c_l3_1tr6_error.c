#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct l3_process {TYPE_2__* st; } ;
struct TYPE_3__ {int debug; } ;
struct TYPE_4__ {TYPE_1__ l3; } ;

/* Variables and functions */
 int L3_DEB_WARN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l3_1tr6_release_req (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3_debug (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l3_1tr6_error(struct l3_process *pc, u_char *msg, struct sk_buff *skb)
{
	dev_kfree_skb(skb);
	if (pc->st->l3.debug & L3_DEB_WARN)
		l3_debug(pc->st, msg);
	l3_1tr6_release_req(pc, 0, NULL);
}