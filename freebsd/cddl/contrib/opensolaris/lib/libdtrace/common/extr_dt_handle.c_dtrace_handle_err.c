#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dp_stmts; } ;
typedef  TYPE_2__ dtrace_prog_t ;
struct TYPE_14__ {scalar_t__* dt_options; TYPE_2__* dt_errprog; void* dt_errarg; int /*<<< orphan*/ * dt_errhdlr; } ;
typedef  TYPE_3__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_handle_err_f ;
struct TYPE_15__ {int /*<<< orphan*/  dted_uarg; } ;
typedef  TYPE_4__ dtrace_ecbdesc_t ;
struct TYPE_16__ {TYPE_1__* ds_desc; } ;
typedef  TYPE_5__ dt_stmt_t ;
struct TYPE_12__ {TYPE_4__* dtsd_ecbdesc; } ;

/* Variables and functions */
 size_t DTRACEOPT_GRABANON ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 int /*<<< orphan*/  DTRACE_C_ZDEFS ; 
 int /*<<< orphan*/  DTRACE_PROBESPEC_NAME ; 
 int /*<<< orphan*/  DT_ECB_ERROR ; 
 int /*<<< orphan*/  EALREADY ; 
 int /*<<< orphan*/  _dt_errprog ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* dt_list_next (int /*<<< orphan*/ *) ; 
 int dt_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (TYPE_3__*) ; 
 TYPE_2__* dtrace_program_strcompile (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dtrace_handle_err(dtrace_hdl_t *dtp, dtrace_handle_err_f *hdlr, void *arg)
{
	dtrace_prog_t *pgp = NULL;
	dt_stmt_t *stp;
	dtrace_ecbdesc_t *edp;

	/*
	 * We don't currently support multiple error handlers.
	 */
	if (dtp->dt_errhdlr != NULL)
		return (dt_set_errno(dtp, EALREADY));

	/*
	 * If the DTRACEOPT_GRABANON is enabled, the anonymous enabling will
	 * already have a dtrace:::ERROR probe enabled; save 'hdlr' and 'arg'
	 * but do not bother compiling and enabling _dt_errprog.
	 */
	if (dtp->dt_options[DTRACEOPT_GRABANON] != DTRACEOPT_UNSET)
		goto out;

	if ((pgp = dtrace_program_strcompile(dtp, _dt_errprog,
	    DTRACE_PROBESPEC_NAME, DTRACE_C_ZDEFS, 0, NULL)) == NULL)
		return (dt_set_errno(dtp, dtrace_errno(dtp)));

	stp = dt_list_next(&pgp->dp_stmts);
	assert(stp != NULL);

	edp = stp->ds_desc->dtsd_ecbdesc;
	assert(edp != NULL);
	edp->dted_uarg = DT_ECB_ERROR;

out:
	dtp->dt_errhdlr = hdlr;
	dtp->dt_errarg = arg;
	dtp->dt_errprog = pgp;

	return (0);
}