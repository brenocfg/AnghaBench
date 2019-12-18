#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int si1; int si2; char* eazmsn; char* phone; } ;
struct TYPE_7__ {int bchannel; int spv; TYPE_1__ setup; } ;
struct l3_process {TYPE_4__* st; TYPE_2__ para; } ;
struct TYPE_8__ {int debug; int /*<<< orphan*/  (* l3l4 ) (TYPE_4__*,int,struct l3_process*) ;} ;
struct TYPE_9__ {TYPE_3__ l3; } ;

/* Variables and functions */
 int CC_SETUP ; 
 int FAC_Activate ; 
 int FAC_SPV ; 
 int INDICATION ; 
 int L3_DEB_WARN ; 
 int /*<<< orphan*/  WE0_chanID ; 
 int /*<<< orphan*/  WE0_destAddr ; 
 int /*<<< orphan*/  WE0_netSpecFac ; 
 int /*<<< orphan*/  WE0_origAddr ; 
 int /*<<< orphan*/  WE6_serviceInd ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int* findie (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iecpy (char*,int*,int) ; 
 int /*<<< orphan*/  l3_1tr6_error (struct l3_process*,char*,struct sk_buff*) ; 
 int /*<<< orphan*/  l3_debug (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  release_l3_process (struct l3_process*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3_1tr6_setup(struct l3_process *pc, u_char pr, void *arg)
{
	u_char *p;
	int bcfound = 0;
	char tmp[80];
	struct sk_buff *skb = arg;

	p = skb->data;

	/* Channel Identification */
	p = skb->data;
	if ((p = findie(p, skb->len, WE0_chanID, 0))) {
		if (p[1] != 1) {
			l3_1tr6_error(pc, "setup wrong chanID len", skb);
			return;
		}
		if ((p[2] & 0xf4) != 0x80) {
			l3_1tr6_error(pc, "setup wrong WE0_chanID", skb);
			return;
		}
		if ((pc->para.bchannel = p[2] & 0x3))
				bcfound++;
	} else {
		l3_1tr6_error(pc, "missing setup chanID", skb);
		return;
	}

	p = skb->data;
	if ((p = findie(p, skb->len, WE6_serviceInd, 6))) {
		pc->para.setup.si1 = p[2];
		pc->para.setup.si2 = p[3];
	} else {
		l3_1tr6_error(pc, "missing setup SI", skb);
		return;
	}

	p = skb->data;
	if ((p = findie(p, skb->len, WE0_destAddr, 0)))
		iecpy(pc->para.setup.eazmsn, p, 1);
	else
		pc->para.setup.eazmsn[0] = 0;

	p = skb->data;
	if ((p = findie(p, skb->len, WE0_origAddr, 0))) {
		iecpy(pc->para.setup.phone, p, 1);
	} else
		pc->para.setup.phone[0] = 0;

	p = skb->data;
	pc->para.spv = 0;
	if ((p = findie(p, skb->len, WE0_netSpecFac, 0))) {
		if ((FAC_SPV == p[3]) || (FAC_Activate == p[3]))
			pc->para.spv = 1;
	}
	dev_kfree_skb(skb);

	/* Signal all services, linklevel takes care of Service-Indicator */
	if (bcfound) {
		if ((pc->para.setup.si1 != 7) && (pc->st->l3.debug & L3_DEB_WARN)) {
			sprintf(tmp, "non-digital call: %s -> %s",
				pc->para.setup.phone,
				pc->para.setup.eazmsn);
			l3_debug(pc->st, tmp);
		}
		newl3state(pc, 6);
		pc->st->l3.l3l4(pc->st, CC_SETUP | INDICATION, pc);
	} else
		release_l3_process(pc);
}