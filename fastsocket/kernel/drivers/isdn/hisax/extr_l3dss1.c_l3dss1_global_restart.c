#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {int bchannel; } ;
struct l3_process {TYPE_4__* st; int /*<<< orphan*/  callref; struct l3_process* next; TYPE_2__ para; int /*<<< orphan*/  timer; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* l4l3 ) (TYPE_4__*,int,struct l3_process*) ;} ;
struct TYPE_8__ {struct l3_process* proc; scalar_t__ debug; } ;
struct TYPE_11__ {TYPE_3__ lli; TYPE_1__ l3; } ;

/* Variables and functions */
 int CC_RESTART ; 
 int DL_DATA ; 
 int /*<<< orphan*/  IE_CHANNEL_ID ; 
 int /*<<< orphan*/  IE_RESTART_IND ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MT_RESTART_ACKNOWLEDGE ; 
 int /*<<< orphan*/  MsgHead (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 int* findie (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_debug (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  l3_msg (TYPE_4__*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int,struct l3_process*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3dss1_global_restart(struct l3_process *pc, u_char pr, void *arg)
{
	u_char tmp[32];
	u_char *p;
	u_char ri, ch = 0, chan = 0;
	int l;
	struct sk_buff *skb = arg;
	struct l3_process *up;

	newl3state(pc, 2);
	L3DelTimer(&pc->timer);
	p = skb->data;
	if ((p = findie(p, skb->len, IE_RESTART_IND, 0))) {
		ri = p[2];
		l3_debug(pc->st, "Restart %x", ri);
	} else {
		l3_debug(pc->st, "Restart without restart IE");
		ri = 0x86;
	}
	p = skb->data;
	if ((p = findie(p, skb->len, IE_CHANNEL_ID, 0))) {
		chan = p[2] & 3;
		ch = p[2];
		if (pc->st->l3.debug)
			l3_debug(pc->st, "Restart for channel %d", chan);
	}
	newl3state(pc, 2);
	up = pc->st->l3.proc;
	while (up) {
		if ((ri & 7) == 7)
			up->st->lli.l4l3(up->st, CC_RESTART | REQUEST, up);
		else if (up->para.bchannel == chan)
			up->st->lli.l4l3(up->st, CC_RESTART | REQUEST, up);
		up = up->next;
	}
	p = tmp;
	MsgHead(p, pc->callref, MT_RESTART_ACKNOWLEDGE);
	if (chan) {
		*p++ = IE_CHANNEL_ID;
		*p++ = 1;
		*p++ = ch | 0x80;
	}
	*p++ = 0x79;		/* RESTART Ind */
	*p++ = 1;
	*p++ = ri;
	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
		return;
	memcpy(skb_put(skb, l), tmp, l);
	newl3state(pc, 0);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
}