#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {int /*<<< orphan*/  dtad_arg; } ;
typedef  TYPE_1__ dtrace_actdesc_t ;
typedef  int /*<<< orphan*/  dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEACT_LIBACT ; 
 int /*<<< orphan*/  DT_ACT_FTRUNCATE ; 
 int /*<<< orphan*/  dt_action_difconst (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dt_stmt_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dt_action_ftruncate(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	dtrace_actdesc_t *ap = dt_stmt_action(dtp, sdp);

	/*
	 * Library actions need a DIFO that serves as an argument.  As
	 * ftruncate() doesn't take an argument, we generate the constant 0
	 * in a DIFO; this constant will be ignored when the ftruncate() is
	 * processed.
	 */
	dt_action_difconst(ap, 0, DTRACEACT_LIBACT);
	ap->dtad_arg = DT_ACT_FTRUNCATE;
}