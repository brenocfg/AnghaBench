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
struct TYPE_8__ {TYPE_3__* dtsd_action_last; TYPE_3__* dtsd_action; TYPE_2__* dtsd_ecbdesc; } ;
typedef  TYPE_1__ dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_9__ {TYPE_3__* dted_action; } ;
typedef  TYPE_2__ dtrace_ecbdesc_t ;
struct TYPE_10__ {uintptr_t dtad_uarg; struct TYPE_10__* dtad_next; } ;
typedef  TYPE_3__ dtrace_actdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 TYPE_3__* dt_alloc (int /*<<< orphan*/ *,int) ; 

dtrace_actdesc_t *
dtrace_stmt_action(dtrace_hdl_t *dtp, dtrace_stmtdesc_t *sdp)
{
	dtrace_actdesc_t *new;
	dtrace_ecbdesc_t *edp = sdp->dtsd_ecbdesc;

	if ((new = dt_alloc(dtp, sizeof (dtrace_actdesc_t))) == NULL)
		return (NULL);

	if (sdp->dtsd_action_last != NULL) {
		assert(sdp->dtsd_action != NULL);
		assert(sdp->dtsd_action_last->dtad_next == NULL);
		sdp->dtsd_action_last->dtad_next = new;
	} else {
		dtrace_actdesc_t *ap = edp->dted_action;

		assert(sdp->dtsd_action == NULL);
		sdp->dtsd_action = new;

		while (ap != NULL && ap->dtad_next != NULL)
			ap = ap->dtad_next;

		if (ap == NULL)
			edp->dted_action = new;
		else
			ap->dtad_next = new;
	}

	sdp->dtsd_action_last = new;
	bzero(new, sizeof (dtrace_actdesc_t));
	new->dtad_uarg = (uintptr_t)sdp;

	return (new);
}