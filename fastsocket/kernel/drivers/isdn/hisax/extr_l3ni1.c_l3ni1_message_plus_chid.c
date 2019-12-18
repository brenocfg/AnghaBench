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
struct TYPE_2__ {int bchannel; } ;
struct l3_process {int /*<<< orphan*/  st; int /*<<< orphan*/  callref; TYPE_1__ para; } ;

/* Variables and functions */
 int DL_DATA ; 
 int /*<<< orphan*/  IE_CHANNEL_ID ; 
 int /*<<< orphan*/  MsgHead (int*,int /*<<< orphan*/ ,int) ; 
 int REQUEST ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
l3ni1_message_plus_chid(struct l3_process *pc, u_char mt)
/* sends an l3 messages plus channel id -  added GE 05/09/00 */
{
	struct sk_buff *skb;
	u_char tmp[16];
	u_char *p = tmp;
	u_char chid;

	chid = (u_char)(pc->para.bchannel & 0x03) | 0x88;
	MsgHead(p, pc->callref, mt);
	*p++ = IE_CHANNEL_ID;
	*p++ = 0x01;
	*p++ = chid;

	if (!(skb = l3_alloc_skb(7)))
		return;
	memcpy(skb_put(skb, 7), tmp, 7);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
}