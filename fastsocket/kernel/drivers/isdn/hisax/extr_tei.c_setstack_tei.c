#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int debug; int /*<<< orphan*/  printdebug; scalar_t__ userint; struct PStack* userdata; int /*<<< orphan*/  state; int /*<<< orphan*/ * fsm; } ;
struct TYPE_7__ {int T202; int debug; int /*<<< orphan*/  t202; TYPE_4__ tei_m; } ;
struct TYPE_6__ {int /*<<< orphan*/  l1tei; } ;
struct TYPE_5__ {int /*<<< orphan*/  l2tei; } ;
struct PStack {TYPE_3__ ma; TYPE_2__ l1; TYPE_1__ l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmInitTimer (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_TEI_NOP ; 
 int /*<<< orphan*/  tei_debug ; 
 int /*<<< orphan*/  tei_l1l2 ; 
 int /*<<< orphan*/  tei_l2tei ; 
 int /*<<< orphan*/  teifsm ; 

void
setstack_tei(struct PStack *st)
{
	st->l2.l2tei = tei_l2tei;
	st->ma.T202 = 2000;	/* T202  2000 milliseconds */
	st->l1.l1tei = tei_l1l2;
	st->ma.debug = 1;
	st->ma.tei_m.fsm = &teifsm;
	st->ma.tei_m.state = ST_TEI_NOP;
	st->ma.tei_m.debug = 1;
	st->ma.tei_m.userdata = st;
	st->ma.tei_m.userint = 0;
	st->ma.tei_m.printdebug = tei_debug;
	FsmInitTimer(&st->ma.tei_m, &st->ma.t202);
}