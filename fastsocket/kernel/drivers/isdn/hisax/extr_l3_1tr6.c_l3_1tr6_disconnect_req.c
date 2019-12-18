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
typedef  int u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ cause; } ;
struct l3_process {int /*<<< orphan*/  timer; int /*<<< orphan*/  st; int /*<<< orphan*/  callref; TYPE_1__ para; } ;

/* Variables and functions */
 int CAUSE_CallRejected ; 
 int CAUSE_UserBusy ; 
 int /*<<< orphan*/  CC_T305 ; 
 int DL_DATA ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_N1_DISC ; 
 int /*<<< orphan*/  MsgHead (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTO_DIS_N1 ; 
 int REQUEST ; 
 int /*<<< orphan*/  StopAllL3Timer (struct l3_process*) ; 
 int /*<<< orphan*/  T305 ; 
 int /*<<< orphan*/  WE0_cause ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
l3_1tr6_disconnect_req(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb;
	u_char tmp[16];
	u_char *p = tmp;
	int l;
	u_char cause = 0x10;
	u_char clen = 1;

	if (pc->para.cause > 0)
		cause = pc->para.cause;
	/* Map DSS1 causes */
	switch (cause & 0x7f) {
		case 0x10:
			clen = 0;
			break;
                case 0x11:
                        cause = CAUSE_UserBusy;
                        break;
		case 0x15:
			cause = CAUSE_CallRejected;
			break;
	}
	StopAllL3Timer(pc);
	MsgHead(p, pc->callref, MT_N1_DISC, PROTO_DIS_N1);
	*p++ = WE0_cause;
	*p++ = clen;		/* Laenge */
	if (clen)
		*p++ = cause | 0x80;
	newl3state(pc, 11);
	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
		return;
	memcpy(skb_put(skb, l), tmp, l);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
	L3AddTimer(&pc->timer, T305, CC_T305);
}