#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cause; } ;
struct l3_process {int debug; TYPE_3__* st; TYPE_1__ para; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int,struct l3_process*) ;} ;
struct TYPE_7__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int CC_RELEASE ; 
 int CONFIRM ; 
 int L3_DEB_WARN ; 
 int /*<<< orphan*/  NO_CAUSE ; 
 int /*<<< orphan*/  StopAllL3Timer (struct l3_process*) ; 
 int /*<<< orphan*/  l3_debug (TYPE_3__*,char*,int) ; 
 int l3ni1_get_cause (struct l3_process*,struct sk_buff*) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni1_release_l3_process (struct l3_process*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3ni1_release_cmpl(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	int ret;

	if ((ret = l3ni1_get_cause(pc, skb))>0) {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "RELCMPL get_cause ret(%d)",ret);
	} else if (ret < 0)
		pc->para.cause = NO_CAUSE;
	StopAllL3Timer(pc);
	newl3state(pc, 0);
	pc->st->l3.l3l4(pc->st, CC_RELEASE | CONFIRM, pc);
	ni1_release_l3_process(pc);
}