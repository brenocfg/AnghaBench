#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_8__ {struct TYPE_8__* pr_argv; struct TYPE_8__* pr_mapping; struct TYPE_8__* pi_enoffs; struct TYPE_8__* pi_offs; struct TYPE_8__* pi_fname; struct TYPE_8__* pi_rname; struct TYPE_8__* pi_next; struct TYPE_8__* pr_inst; struct TYPE_8__* pr_xargv; struct TYPE_8__* pr_nargv; int /*<<< orphan*/  pr_xargs; int /*<<< orphan*/  pr_nargs; TYPE_1__* pr_pvp; } ;
typedef  TYPE_2__ dt_probe_t ;
typedef  TYPE_2__ dt_probe_instance_t ;
struct TYPE_9__ {int /*<<< orphan*/ * pcb_hdl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pv_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_node_list_free (int /*<<< orphan*/ *) ; 
 TYPE_4__* yypcb ; 

void
dt_probe_destroy(dt_probe_t *prp)
{
	dt_probe_instance_t *pip, *pip_next;
	dtrace_hdl_t *dtp;

	if (prp->pr_pvp != NULL)
		dtp = prp->pr_pvp->pv_hdl;
	else
		dtp = yypcb->pcb_hdl;

	dt_node_list_free(&prp->pr_nargs);
	dt_node_list_free(&prp->pr_xargs);

	dt_free(dtp, prp->pr_nargv);
	dt_free(dtp, prp->pr_xargv);

	for (pip = prp->pr_inst; pip != NULL; pip = pip_next) {
		pip_next = pip->pi_next;
		dt_free(dtp, pip->pi_rname);
		dt_free(dtp, pip->pi_fname);
		dt_free(dtp, pip->pi_offs);
		dt_free(dtp, pip->pi_enoffs);
		dt_free(dtp, pip);
	}

	dt_free(dtp, prp->pr_mapping);
	dt_free(dtp, prp->pr_argv);
	dt_free(dtp, prp);
}