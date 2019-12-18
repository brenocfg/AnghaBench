#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* printdebug ) (TYPE_3__*,char*,int) ;} ;
struct TYPE_7__ {int ri; int N202; int /*<<< orphan*/  T202; int /*<<< orphan*/  t202; TYPE_3__ tei_m; scalar_t__ debug; } ;
struct TYPE_6__ {int tei; } ;
struct PStack {TYPE_2__ ma; TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_T202 ; 
 int /*<<< orphan*/  FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmChangeState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID_REQUEST ; 
 int /*<<< orphan*/  ST_TEI_IDREQ ; 
 int /*<<< orphan*/  put_tei_msg (struct PStack*,int /*<<< orphan*/ ,int,int) ; 
 int random_ri () ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char*,int) ; 

__attribute__((used)) static void
tei_id_request(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	if (st->l2.tei != -1) {
		st->ma.tei_m.printdebug(&st->ma.tei_m,
			"assign request for allready asigned tei %d",
			st->l2.tei);
		return;
	}
	st->ma.ri = random_ri();
	if (st->ma.debug)
		st->ma.tei_m.printdebug(&st->ma.tei_m,
			"assign request ri %d", st->ma.ri);
	put_tei_msg(st, ID_REQUEST, st->ma.ri, 127);
	FsmChangeState(&st->ma.tei_m, ST_TEI_IDREQ);
	FsmAddTimer(&st->ma.t202, st->ma.T202, EV_T202, NULL, 1);
	st->ma.N202 = 3;
}