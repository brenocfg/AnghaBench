#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_7__ {void* dtad_arg; void* dtad_kind; void* dtad_difo; } ;
typedef  TYPE_1__ dtrace_actdesc_t ;
struct TYPE_8__ {struct TYPE_8__* dn_list; struct TYPE_8__* dn_args; } ;
typedef  TYPE_2__ dt_node_t ;

/* Variables and functions */
 void* DTRACEACT_LIBACT ; 
 void* DT_ACT_SETOPT ; 
 int /*<<< orphan*/  dt_action_difconst (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 void* dt_as (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* dt_stmt_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yypcb ; 

__attribute__((used)) static void
dt_action_setopt(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	dtrace_actdesc_t *ap;
	dt_node_t *arg0, *arg1;

	/*
	 * The prototype guarantees that we are called with either one or
	 * two arguments, and that any arguments that are present are strings.
	 */
	arg0 = dnp->dn_args;
	arg1 = arg0->dn_list;

	ap = dt_stmt_action(dtp, sdp);
	dt_cg(yypcb, arg0);
	ap->dtad_difo = dt_as(yypcb);
	ap->dtad_kind = DTRACEACT_LIBACT;
	ap->dtad_arg = DT_ACT_SETOPT;

	ap = dt_stmt_action(dtp, sdp);

	if (arg1 == NULL) {
		dt_action_difconst(ap, 0, DTRACEACT_LIBACT);
	} else {
		dt_cg(yypcb, arg1);
		ap->dtad_difo = dt_as(yypcb);
		ap->dtad_kind = DTRACEACT_LIBACT;
	}

	ap->dtad_arg = DT_ACT_SETOPT;
}