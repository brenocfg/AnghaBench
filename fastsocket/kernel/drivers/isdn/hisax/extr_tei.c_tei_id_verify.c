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
struct TYPE_7__ {int /*<<< orphan*/  (* printdebug ) (TYPE_3__*,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int N202; int /*<<< orphan*/  T202; int /*<<< orphan*/  t202; TYPE_3__ tei_m; scalar_t__ debug; } ;
struct TYPE_5__ {int /*<<< orphan*/  tei; } ;
struct PStack {TYPE_2__ ma; TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_T202 ; 
 int /*<<< orphan*/  FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmChangeState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID_VERIFY ; 
 int /*<<< orphan*/  ST_TEI_IDVERIFY ; 
 int /*<<< orphan*/  put_tei_msg (struct PStack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tei_id_verify(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	if (st->ma.debug)
		st->ma.tei_m.printdebug(&st->ma.tei_m,
			"id verify request for tei %d", st->l2.tei);
	put_tei_msg(st, ID_VERIFY, 0, st->l2.tei);
	FsmChangeState(&st->ma.tei_m, ST_TEI_IDVERIFY);
	FsmAddTimer(&st->ma.t202, st->ma.T202, EV_T202, NULL, 2);
	st->ma.N202 = 2;
}