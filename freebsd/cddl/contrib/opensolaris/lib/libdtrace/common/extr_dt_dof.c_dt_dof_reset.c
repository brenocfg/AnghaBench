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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  dtrace_prog_t ;
struct TYPE_8__ {int /*<<< orphan*/  ddo_xlms; int /*<<< orphan*/  ddo_rels; int /*<<< orphan*/  ddo_enoffs; int /*<<< orphan*/  ddo_offs; int /*<<< orphan*/  ddo_args; int /*<<< orphan*/  ddo_probes; int /*<<< orphan*/  ddo_udata; int /*<<< orphan*/  ddo_ldata; int /*<<< orphan*/  ddo_strs; int /*<<< orphan*/  ddo_secs; void** ddo_xlexport; void** ddo_xlimport; void* ddo_strsec; scalar_t__ ddo_nsecs; int /*<<< orphan*/ * ddo_pgp; TYPE_1__* ddo_hdl; } ;
struct TYPE_7__ {int dt_xlatorid; TYPE_2__ dt_dof; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_dof_t ;
typedef  int /*<<< orphan*/  dof_secidx_t ;

/* Variables and functions */
 void* DOF_SECIDX_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* dt_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dt_buf_reset (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_free (TYPE_1__*,void**) ; 

__attribute__((used)) static int
dt_dof_reset(dtrace_hdl_t *dtp, dtrace_prog_t *pgp)
{
	dt_dof_t *ddo = &dtp->dt_dof;
	uint_t i, nx = dtp->dt_xlatorid;

	assert(ddo->ddo_hdl == dtp);
	ddo->ddo_pgp = pgp;

	ddo->ddo_nsecs = 0;
	ddo->ddo_strsec = DOF_SECIDX_NONE;

	dt_free(dtp, ddo->ddo_xlimport);
	dt_free(dtp, ddo->ddo_xlexport);

	ddo->ddo_xlimport = dt_alloc(dtp, sizeof (dof_secidx_t) * nx);
	ddo->ddo_xlexport = dt_alloc(dtp, sizeof (dof_secidx_t) * nx);

	if (nx != 0 && (ddo->ddo_xlimport == NULL || ddo->ddo_xlexport == NULL))
		return (-1); /* errno is set for us */

	for (i = 0; i < nx; i++) {
		ddo->ddo_xlimport[i] = DOF_SECIDX_NONE;
		ddo->ddo_xlexport[i] = DOF_SECIDX_NONE;
	}

	dt_buf_reset(dtp, &ddo->ddo_secs);
	dt_buf_reset(dtp, &ddo->ddo_strs);
	dt_buf_reset(dtp, &ddo->ddo_ldata);
	dt_buf_reset(dtp, &ddo->ddo_udata);

	dt_buf_reset(dtp, &ddo->ddo_probes);
	dt_buf_reset(dtp, &ddo->ddo_args);
	dt_buf_reset(dtp, &ddo->ddo_offs);
	dt_buf_reset(dtp, &ddo->ddo_enoffs);
	dt_buf_reset(dtp, &ddo->ddo_rels);

	dt_buf_reset(dtp, &ddo->ddo_xlms);
	return (0);
}