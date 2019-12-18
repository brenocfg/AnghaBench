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
struct TYPE_6__ {int /*<<< orphan*/  ddo_xlms; int /*<<< orphan*/  ddo_rels; int /*<<< orphan*/  ddo_enoffs; int /*<<< orphan*/  ddo_offs; int /*<<< orphan*/  ddo_args; int /*<<< orphan*/  ddo_probes; int /*<<< orphan*/  ddo_udata; int /*<<< orphan*/  ddo_ldata; int /*<<< orphan*/  ddo_strs; int /*<<< orphan*/  ddo_secs; int /*<<< orphan*/ * ddo_xlexport; int /*<<< orphan*/ * ddo_xlimport; int /*<<< orphan*/  ddo_strsec; scalar_t__ ddo_nsecs; TYPE_1__* ddo_hdl; } ;
struct TYPE_5__ {TYPE_2__ dt_dof; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_dof_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOF_SECIDX_NONE ; 
 int /*<<< orphan*/  dt_buf_create (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
dt_dof_init(dtrace_hdl_t *dtp)
{
	dt_dof_t *ddo = &dtp->dt_dof;

	ddo->ddo_hdl = dtp;
	ddo->ddo_nsecs = 0;
	ddo->ddo_strsec = DOF_SECIDX_NONE;
	ddo->ddo_xlimport = NULL;
	ddo->ddo_xlexport = NULL;

	dt_buf_create(dtp, &ddo->ddo_secs, "section headers", 0);
	dt_buf_create(dtp, &ddo->ddo_strs, "string table", 0);
	dt_buf_create(dtp, &ddo->ddo_ldata, "loadable data", 0);
	dt_buf_create(dtp, &ddo->ddo_udata, "unloadable data", 0);

	dt_buf_create(dtp, &ddo->ddo_probes, "probe data", 0);
	dt_buf_create(dtp, &ddo->ddo_args, "probe args", 0);
	dt_buf_create(dtp, &ddo->ddo_offs, "probe offs", 0);
	dt_buf_create(dtp, &ddo->ddo_enoffs, "probe is-enabled offs", 0);
	dt_buf_create(dtp, &ddo->ddo_rels, "probe rels", 0);

	dt_buf_create(dtp, &ddo->ddo_xlms, "xlate members", 0);
}