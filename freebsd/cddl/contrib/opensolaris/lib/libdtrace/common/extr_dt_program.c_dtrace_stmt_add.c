#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_stmts; } ;
typedef  TYPE_1__ dtrace_prog_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_7__ {int /*<<< orphan*/ * ds_desc; } ;
typedef  TYPE_2__ dt_stmt_t ;

/* Variables and functions */
 TYPE_2__* dt_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dt_list_append (int /*<<< orphan*/ *,TYPE_2__*) ; 

int
dtrace_stmt_add(dtrace_hdl_t *dtp, dtrace_prog_t *pgp, dtrace_stmtdesc_t *sdp)
{
	dt_stmt_t *stp = dt_alloc(dtp, sizeof (dt_stmt_t));

	if (stp == NULL)
		return (-1); /* errno is set for us */

	dt_list_append(&pgp->dp_stmts, stp);
	stp->ds_desc = sdp;

	return (0);
}