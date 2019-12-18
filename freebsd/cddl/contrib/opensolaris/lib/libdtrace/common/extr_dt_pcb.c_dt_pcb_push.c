#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dt_gen; TYPE_2__* dt_pcb; int /*<<< orphan*/  dt_globals; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_9__ {struct TYPE_9__* pcb_prev; TYPE_1__* pcb_hdl; int /*<<< orphan*/  pcb_ir; int /*<<< orphan*/  pcb_globals; int /*<<< orphan*/  pcb_dstack; } ;
typedef  TYPE_2__ dt_pcb_t ;
struct TYPE_10__ {scalar_t__ pcb_yystate; TYPE_1__* pcb_hdl; } ;

/* Variables and functions */
 scalar_t__ YYS_DONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dt_idstack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_irlist_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_scope_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyinit (TYPE_2__*) ; 
 TYPE_3__* yypcb ; 

void
dt_pcb_push(dtrace_hdl_t *dtp, dt_pcb_t *pcb)
{
	/*
	 * Since lex/yacc are not re-entrant and we don't implement state save,
	 * assert that if another PCB is active, it is from the same handle and
	 * has completed execution of yyparse().  If the first assertion fires,
	 * the caller is calling libdtrace without proper MT locking.  If the
	 * second assertion fires, dt_compile() is being called recursively
	 * from an illegal location in libdtrace, or a dt_pcb_pop() is missing.
	 */
	if (yypcb != NULL) {
		assert(yypcb->pcb_hdl == dtp);
		assert(yypcb->pcb_yystate == YYS_DONE);
	}

	bzero(pcb, sizeof (dt_pcb_t));

	dt_scope_create(&pcb->pcb_dstack);
	dt_idstack_push(&pcb->pcb_globals, dtp->dt_globals);
	dt_irlist_create(&pcb->pcb_ir);

	pcb->pcb_hdl = dtp;
	pcb->pcb_prev = dtp->dt_pcb;

	dtp->dt_pcb = pcb;
	dtp->dt_gen++;

	yyinit(pcb);
}