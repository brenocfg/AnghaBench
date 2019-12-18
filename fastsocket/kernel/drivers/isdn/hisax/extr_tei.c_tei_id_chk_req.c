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
struct sk_buff {int* data; } ;
struct TYPE_6__ {int tei; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* printdebug ) (TYPE_3__*,char*,int) ;} ;
struct TYPE_5__ {TYPE_3__ tei_m; int /*<<< orphan*/  t202; scalar_t__ debug; } ;
struct PStack {TYPE_2__ l2; TYPE_1__ ma; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int GROUP_TEI ; 
 int /*<<< orphan*/  ID_CHK_RES ; 
 int /*<<< orphan*/  ST_TEI_NOP ; 
 int /*<<< orphan*/  put_tei_msg (struct PStack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  random_ri () ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,int) ; 

__attribute__((used)) static void
tei_id_chk_req(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;
	int tei;

	tei = skb->data[4] >> 1;
	if (st->ma.debug)
		st->ma.tei_m.printdebug(&st->ma.tei_m,
			"identity check req tei %d", tei);
	if ((st->l2.tei != -1) && ((tei == GROUP_TEI) || (tei == st->l2.tei))) {
		FsmDelTimer(&st->ma.t202, 4);
		FsmChangeState(&st->ma.tei_m, ST_TEI_NOP);
		put_tei_msg(st, ID_CHK_RES, random_ri(), st->l2.tei);
	}
}