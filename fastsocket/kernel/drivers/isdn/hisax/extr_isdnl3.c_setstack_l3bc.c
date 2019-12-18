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
struct TYPE_6__ {int /*<<< orphan*/  l4l3; } ;
struct TYPE_4__ {int debug; int /*<<< orphan*/  printdebug; scalar_t__ userint; struct PStack* userdata; int /*<<< orphan*/  state; int /*<<< orphan*/ * fsm; } ;
struct TYPE_5__ {int /*<<< orphan*/  debug_id; TYPE_1__ l3m; int /*<<< orphan*/  squeue; int /*<<< orphan*/ * global; int /*<<< orphan*/ * proc; } ;
struct PStack {TYPE_3__ lli; TYPE_2__ l3; } ;
struct Channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_L3_LC_REL ; 
 int /*<<< orphan*/  isdnl3_trans ; 
 int /*<<< orphan*/  l3fsm ; 
 int /*<<< orphan*/  l3m_debug ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void
setstack_l3bc(struct PStack *st, struct Channel *chanp)
{

	st->l3.proc   = NULL;
	st->l3.global = NULL;
	skb_queue_head_init(&st->l3.squeue);
	st->l3.l3m.fsm = &l3fsm;
	st->l3.l3m.state = ST_L3_LC_REL;
	st->l3.l3m.debug = 1;
	st->l3.l3m.userdata = st;
	st->l3.l3m.userint = 0;
	st->l3.l3m.printdebug = l3m_debug;
	strcpy(st->l3.debug_id, "L3BC ");
	st->lli.l4l3 = isdnl3_trans;
}