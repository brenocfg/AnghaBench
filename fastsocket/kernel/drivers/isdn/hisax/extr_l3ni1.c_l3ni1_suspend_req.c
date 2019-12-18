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
typedef  int u_char ;
struct sk_buff {int dummy; } ;
struct l3_process {int /*<<< orphan*/  timer; int /*<<< orphan*/  st; int /*<<< orphan*/  callref; TYPE_2__* chan; } ;
struct TYPE_3__ {int* phone; } ;
struct TYPE_4__ {TYPE_1__ setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_T319 ; 
 int DL_DATA ; 
 int /*<<< orphan*/  IE_CALL_ID ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_SUSPEND ; 
 int /*<<< orphan*/  MsgHead (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 int /*<<< orphan*/  T319 ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
l3ni1_suspend_req(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb;
	u_char tmp[32];
	u_char *p = tmp;
	u_char i, l;
	u_char *msg = pc->chan->setup.phone;

	MsgHead(p, pc->callref, MT_SUSPEND);
	l = *msg++;
	if (l && (l <= 10)) {	/* Max length 10 octets */
		*p++ = IE_CALL_ID;
		*p++ = l;
		for (i = 0; i < l; i++)
			*p++ = *msg++;
	} else if (l) {
		l3_debug(pc->st, "SUS wrong CALL_ID len %d", l);
		return;
	}
	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
		return;
	memcpy(skb_put(skb, l), tmp, l);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
	newl3state(pc, 15);
	L3AddTimer(&pc->timer, T319, CC_T319);
}