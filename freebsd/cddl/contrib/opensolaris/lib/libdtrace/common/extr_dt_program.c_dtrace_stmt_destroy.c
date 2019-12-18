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
struct TYPE_7__ {uintptr_t dtad_uarg; TYPE_2__* dtsd_ecbdesc; struct TYPE_7__* dtsd_strdata; int /*<<< orphan*/ * dtsd_fmtdata; struct TYPE_7__* dtad_next; int /*<<< orphan*/  dtad_difo; struct TYPE_7__* dtsd_action; struct TYPE_7__* dtsd_action_last; } ;
typedef  TYPE_1__ dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_8__ {TYPE_1__* dted_action; } ;
typedef  TYPE_2__ dtrace_ecbdesc_t ;
typedef  TYPE_1__ dtrace_actdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_difo_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_ecbdesc_release (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_printf_destroy (int /*<<< orphan*/ *) ; 

void
dtrace_stmt_destroy(dtrace_hdl_t *dtp, dtrace_stmtdesc_t *sdp)
{
	dtrace_ecbdesc_t *edp = sdp->dtsd_ecbdesc;

	/*
	 * We need to remove any actions that we have on this ECB, and
	 * remove our hold on the ECB itself.
	 */
	if (sdp->dtsd_action != NULL) {
		dtrace_actdesc_t *last = sdp->dtsd_action_last;
		dtrace_actdesc_t *ap, *next;

		assert(last != NULL);

		for (ap = edp->dted_action; ap != NULL; ap = ap->dtad_next) {
			if (ap == sdp->dtsd_action)
				break;

			if (ap->dtad_next == sdp->dtsd_action)
				break;
		}

		assert(ap != NULL);

		if (ap == edp->dted_action)
			edp->dted_action = last->dtad_next;
		else
			ap->dtad_next = last->dtad_next;

		/*
		 * We have now removed our action list from its ECB; we can
		 * safely destroy the list.
		 */
		last->dtad_next = NULL;

		for (ap = sdp->dtsd_action; ap != NULL; ap = next) {
			assert(ap->dtad_uarg == (uintptr_t)sdp);
			dt_difo_free(dtp, ap->dtad_difo);
			next = ap->dtad_next;
			dt_free(dtp, ap);
		}
	}

	if (sdp->dtsd_fmtdata != NULL)
		dt_printf_destroy(sdp->dtsd_fmtdata);
	dt_free(dtp, sdp->dtsd_strdata);

	dt_ecbdesc_release(dtp, sdp->dtsd_ecbdesc);
	dt_free(dtp, sdp);
}