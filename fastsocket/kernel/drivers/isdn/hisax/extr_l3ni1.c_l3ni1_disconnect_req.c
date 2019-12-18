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
typedef  int u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {char* uus1_data; } ;
struct TYPE_6__ {TYPE_2__ ni1; } ;
struct TYPE_4__ {scalar_t__ cause; } ;
struct l3_process {int /*<<< orphan*/  timer; int /*<<< orphan*/  st; TYPE_3__ prot; int /*<<< orphan*/  callref; TYPE_1__ para; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_T305 ; 
 int DL_DATA ; 
 int /*<<< orphan*/  IE_CAUSE ; 
 int /*<<< orphan*/  IE_USER_USER ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DISCONNECT ; 
 int /*<<< orphan*/  MsgHead (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NO_CAUSE ; 
 int REQUEST ; 
 int /*<<< orphan*/  StopAllL3Timer (struct l3_process*) ; 
 int /*<<< orphan*/  T305 ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  strcpy (int*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
l3ni1_disconnect_req(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb;
	u_char tmp[16+40];
	u_char *p = tmp;
	int l;
	u_char cause = 16;

	if (pc->para.cause != NO_CAUSE)
		cause = pc->para.cause;

	StopAllL3Timer(pc);

	MsgHead(p, pc->callref, MT_DISCONNECT);

	*p++ = IE_CAUSE;
	*p++ = 0x2;
	*p++ = 0x80;
	*p++ = cause | 0x80;

        if (pc->prot.ni1.uus1_data[0])
	 { *p++ = IE_USER_USER; /* UUS info element */
           *p++ = strlen(pc->prot.ni1.uus1_data) + 1;
           *p++ = 0x04; /* IA5 chars */
           strcpy(p,pc->prot.ni1.uus1_data);
           p += strlen(pc->prot.ni1.uus1_data);
           pc->prot.ni1.uus1_data[0] = '\0';   
         } 

	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
		return;
	memcpy(skb_put(skb, l), tmp, l);
	newl3state(pc, 11);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
	L3AddTimer(&pc->timer, T305, CC_T305);
}