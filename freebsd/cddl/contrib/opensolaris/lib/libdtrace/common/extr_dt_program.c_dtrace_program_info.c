#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ dpi_recgens; int /*<<< orphan*/  dpi_aggregates; int /*<<< orphan*/  dpi_speculations; void* dpi_stmtattr; void* dpi_descattr; } ;
typedef  TYPE_4__ dtrace_proginfo_t ;
struct TYPE_21__ {TYPE_1__* ds_desc; } ;
struct TYPE_18__ {TYPE_8__ dp_stmts; } ;
typedef  TYPE_5__ dtrace_prog_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_19__ {TYPE_7__* dted_action; } ;
typedef  TYPE_6__ dtrace_ecbdesc_t ;
struct TYPE_20__ {scalar_t__ dtad_kind; TYPE_3__* dtad_difo; scalar_t__ dtad_arg; struct TYPE_20__* dtad_next; } ;
typedef  TYPE_7__ dtrace_actdesc_t ;
typedef  TYPE_8__ dt_stmt_t ;
struct TYPE_15__ {scalar_t__ dtdt_kind; scalar_t__ dtdt_size; } ;
struct TYPE_16__ {TYPE_2__ dtdo_rtype; } ;
struct TYPE_14__ {int /*<<< orphan*/  dtsd_stmtattr; int /*<<< orphan*/  dtsd_descattr; TYPE_6__* dtsd_ecbdesc; } ;

/* Variables and functions */
 scalar_t__ DIF_TYPE_CTF ; 
 scalar_t__ DTRACEACT_DIFEXPR ; 
 scalar_t__ DTRACEACT_ISAGG (scalar_t__) ; 
 scalar_t__ DTRACEACT_ISDESTRUCTIVE (scalar_t__) ; 
 scalar_t__ DTRACEACT_SPECULATE ; 
 void* _dtrace_defattr ; 
 void* _dtrace_maxattr ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 void* dt_attr_min (int /*<<< orphan*/ ,void*) ; 
 TYPE_8__* dt_list_next (TYPE_8__*) ; 

void
dtrace_program_info(dtrace_hdl_t *dtp, dtrace_prog_t *pgp,
    dtrace_proginfo_t *pip)
{
	dt_stmt_t *stp;
	dtrace_actdesc_t *ap;
	dtrace_ecbdesc_t *last = NULL;

	if (pip == NULL)
		return;

	bzero(pip, sizeof (dtrace_proginfo_t));

	if (dt_list_next(&pgp->dp_stmts) != NULL) {
		pip->dpi_descattr = _dtrace_maxattr;
		pip->dpi_stmtattr = _dtrace_maxattr;
	} else {
		pip->dpi_descattr = _dtrace_defattr;
		pip->dpi_stmtattr = _dtrace_defattr;
	}

	for (stp = dt_list_next(&pgp->dp_stmts); stp; stp = dt_list_next(stp)) {
		dtrace_ecbdesc_t *edp = stp->ds_desc->dtsd_ecbdesc;

		if (edp == last)
			continue;
		last = edp;

		pip->dpi_descattr =
		    dt_attr_min(stp->ds_desc->dtsd_descattr, pip->dpi_descattr);

		pip->dpi_stmtattr =
		    dt_attr_min(stp->ds_desc->dtsd_stmtattr, pip->dpi_stmtattr);

		/*
		 * If there aren't any actions, account for the fact that
		 * recording the epid will generate a record.
		 */
		if (edp->dted_action == NULL)
			pip->dpi_recgens++;

		for (ap = edp->dted_action; ap != NULL; ap = ap->dtad_next) {
			if (ap->dtad_kind == DTRACEACT_SPECULATE) {
				pip->dpi_speculations++;
				continue;
			}

			if (DTRACEACT_ISAGG(ap->dtad_kind)) {
				pip->dpi_recgens -= ap->dtad_arg;
				pip->dpi_aggregates++;
				continue;
			}

			if (DTRACEACT_ISDESTRUCTIVE(ap->dtad_kind))
				continue;

			if (ap->dtad_kind == DTRACEACT_DIFEXPR &&
			    ap->dtad_difo->dtdo_rtype.dtdt_kind ==
			    DIF_TYPE_CTF &&
			    ap->dtad_difo->dtdo_rtype.dtdt_size == 0)
				continue;

			pip->dpi_recgens++;
		}
	}
}