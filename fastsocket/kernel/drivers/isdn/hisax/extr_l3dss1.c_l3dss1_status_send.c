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
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int cause; } ;
struct l3_process {int state; int /*<<< orphan*/  st; TYPE_1__ para; int /*<<< orphan*/  callref; } ;

/* Variables and functions */
 int DL_DATA ; 
 int /*<<< orphan*/  IE_CALL_STATE ; 
 int /*<<< orphan*/  IE_CAUSE ; 
 int /*<<< orphan*/  MT_STATUS ; 
 int /*<<< orphan*/  MsgHead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
l3dss1_status_send(struct l3_process *pc, u_char pr, void *arg)
{
	u_char tmp[16];
	u_char *p = tmp;
	int l;
	struct sk_buff *skb;

	MsgHead(p, pc->callref, MT_STATUS);

	*p++ = IE_CAUSE;
	*p++ = 0x2;
	*p++ = 0x80;
	*p++ = pc->para.cause | 0x80;

	*p++ = IE_CALL_STATE;
	*p++ = 0x1;
	*p++ = pc->state & 0x3f;

	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
		return;
	memcpy(skb_put(skb, l), tmp, l);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
}