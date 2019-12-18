#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int* data; } ;
struct TYPE_10__ {scalar_t__ hardware; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* l3l2 ) (struct PStack*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* printdebug ) (TYPE_5__*,char*,int) ;} ;
struct TYPE_8__ {TYPE_5__ tei_m; int /*<<< orphan*/  t202; scalar_t__ debug; } ;
struct TYPE_7__ {int tei; } ;
struct PStack {TYPE_4__ l1; TYPE_3__ l3; TYPE_2__ ma; TYPE_1__ l2; } ;
struct IsdnCardState {int /*<<< orphan*/  (* cardmsg ) (struct IsdnCardState*,int,int /*<<< orphan*/ *) ;} ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int GROUP_TEI ; 
 int MDL_REMOVE ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_TEI_NOP ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  stub2 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tei_id_remove(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;
	struct IsdnCardState *cs;
	int tei;

	tei = skb->data[4] >> 1;
	if (st->ma.debug)
		st->ma.tei_m.printdebug(&st->ma.tei_m,
			"identity remove tei %d", tei);
	if ((st->l2.tei != -1) && ((tei == GROUP_TEI) || (tei == st->l2.tei))) {
		FsmDelTimer(&st->ma.t202, 5);
		FsmChangeState(&st->ma.tei_m, ST_TEI_NOP);
		st->l3.l3l2(st, MDL_REMOVE | REQUEST, NULL);
		cs = (struct IsdnCardState *) st->l1.hardware;
		cs->cardmsg(cs, MDL_REMOVE | REQUEST, NULL);
	}
}