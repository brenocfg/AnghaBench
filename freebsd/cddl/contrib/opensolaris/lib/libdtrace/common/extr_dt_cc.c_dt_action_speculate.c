#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_5__ {int /*<<< orphan*/  dtad_kind; int /*<<< orphan*/  dtad_difo; } ;
typedef  TYPE_1__ dtrace_actdesc_t ;
struct TYPE_6__ {int /*<<< orphan*/  dn_args; } ;
typedef  TYPE_2__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEACT_SPECULATE ; 
 int /*<<< orphan*/  dt_as (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dt_stmt_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yypcb ; 

__attribute__((used)) static void
dt_action_speculate(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	dtrace_actdesc_t *ap = dt_stmt_action(dtp, sdp);

	dt_cg(yypcb, dnp->dn_args);
	ap->dtad_difo = dt_as(yypcb);
	ap->dtad_kind = DTRACEACT_SPECULATE;
}