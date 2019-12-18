#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct l3_process {int debug; int state; int /*<<< orphan*/  timer; TYPE_2__* st; int /*<<< orphan*/  callref; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_2__*,int,struct l3_process*) ;} ;
struct TYPE_6__ {TYPE_1__ l3; } ;

/* Variables and functions */
 int CC_DISCONNECT ; 
 int /*<<< orphan*/  CC_T308_1 ; 
 int ERR_IE_COMPREHENSION ; 
 int ERR_IE_UNRECOGNIZED ; 
 int /*<<< orphan*/  IE_FACILITY ; 
 int INDICATION ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int L3_DEB_WARN ; 
 int /*<<< orphan*/  MT_RELEASE ; 
 int /*<<< orphan*/  StopAllL3Timer (struct l3_process*) ; 
 int /*<<< orphan*/  T308 ; 
 int check_infoelements (struct l3_process*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int* findie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie_DISCONNECT ; 
 int /*<<< orphan*/  l3_debug (TYPE_2__*,char*,int) ; 
 int l3ni1_get_cause (struct l3_process*,struct sk_buff*) ; 
 int /*<<< orphan*/  l3ni1_message_cause (struct l3_process*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l3ni1_parse_facility (TYPE_2__*,struct l3_process*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  l3ni1_release_req (struct l3_process*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3ni1_disconnect(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	u_char *p;
	int ret;
	u_char cause = 0;

	StopAllL3Timer(pc);
	if ((ret = l3ni1_get_cause(pc, skb))) {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "DISC get_cause ret(%d)", ret);
		if (ret < 0)
			cause = 96;
		else if (ret > 0)
			cause = 100;
	} 
	if ((p = findie(skb->data, skb->len, IE_FACILITY, 0)))
		l3ni1_parse_facility(pc->st, pc, pc->callref, p);
	ret = check_infoelements(pc, skb, ie_DISCONNECT);
	if (ERR_IE_COMPREHENSION == ret)
		cause = 96;
	else if ((!cause) && (ERR_IE_UNRECOGNIZED == ret))
		cause = 99;
	ret = pc->state;
	newl3state(pc, 12);
	if (cause)
		newl3state(pc, 19);
       	if (11 != ret)
		pc->st->l3.l3l4(pc->st, CC_DISCONNECT | INDICATION, pc);
       	else if (!cause)
		   l3ni1_release_req(pc, pr, NULL);
	if (cause) {
		l3ni1_message_cause(pc, MT_RELEASE, cause);
		L3AddTimer(&pc->timer, T308, CC_T308_1);
	}
}