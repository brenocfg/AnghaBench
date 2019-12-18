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
struct TYPE_7__ {int /*<<< orphan*/  ddo_xlms; int /*<<< orphan*/  ddo_rels; int /*<<< orphan*/  ddo_enoffs; int /*<<< orphan*/  ddo_offs; int /*<<< orphan*/  ddo_args; int /*<<< orphan*/  ddo_probes; int /*<<< orphan*/  ddo_udata; int /*<<< orphan*/  ddo_ldata; int /*<<< orphan*/  ddo_strs; int /*<<< orphan*/  ddo_secs; int /*<<< orphan*/  ddo_xlexport; int /*<<< orphan*/  ddo_xlimport; } ;
struct TYPE_6__ {TYPE_2__ dt_dof; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_dof_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_buf_destroy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
dt_dof_fini(dtrace_hdl_t *dtp)
{
	dt_dof_t *ddo = &dtp->dt_dof;

	dt_free(dtp, ddo->ddo_xlimport);
	dt_free(dtp, ddo->ddo_xlexport);

	dt_buf_destroy(dtp, &ddo->ddo_secs);
	dt_buf_destroy(dtp, &ddo->ddo_strs);
	dt_buf_destroy(dtp, &ddo->ddo_ldata);
	dt_buf_destroy(dtp, &ddo->ddo_udata);

	dt_buf_destroy(dtp, &ddo->ddo_probes);
	dt_buf_destroy(dtp, &ddo->ddo_args);
	dt_buf_destroy(dtp, &ddo->ddo_offs);
	dt_buf_destroy(dtp, &ddo->ddo_enoffs);
	dt_buf_destroy(dtp, &ddo->ddo_rels);

	dt_buf_destroy(dtp, &ddo->ddo_xlms);
}