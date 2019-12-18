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
struct TYPE_4__ {int /*<<< orphan*/  (* printdebug ) (struct FsmInst*,char*,int) ;} ;
struct teimgr {TYPE_1__* l2; TYPE_2__ tei_m; int /*<<< orphan*/  timer; } ;
struct FsmInst {struct teimgr* userdata; } ;
struct TYPE_3__ {int tei; } ;

/* Variables and functions */
 int DEBUG_L2_TEI ; 
 int GROUP_TEI ; 
 int /*<<< orphan*/  MDL_REMOVE_REQ ; 
 int /*<<< orphan*/  ST_TEI_NOP ; 
 int* debug ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct FsmInst*,char*,int) ; 
 int /*<<< orphan*/  tei_l2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tei_id_remove(struct FsmInst *fi, int event, void *arg)
{
	struct teimgr *tm = fi->userdata;
	u_char *dp = arg;
	int tei;

	tei = *(dp+3) >> 1;
	if (*debug & DEBUG_L2_TEI)
		tm->tei_m.printdebug(fi, "identity remove tei %d", tei);
	if ((tm->l2->tei != GROUP_TEI) &&
	    ((tei == GROUP_TEI) || (tei == tm->l2->tei))) {
		mISDN_FsmDelTimer(&tm->timer, 5);
		mISDN_FsmChangeState(&tm->tei_m, ST_TEI_NOP);
		tei_l2(tm->l2, MDL_REMOVE_REQ, 0);
	}
}