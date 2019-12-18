#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
struct TYPE_13__ {scalar_t__ di_vers; } ;
struct TYPE_12__ {scalar_t__ di_vers; } ;
struct TYPE_15__ {TYPE_2__ dx_ptrid; TYPE_1__ dx_souid; } ;
struct TYPE_14__ {scalar_t__ dt_vmax; int /*<<< orphan*/  dt_tls; int /*<<< orphan*/  dt_globals; int /*<<< orphan*/  dt_aggs; int /*<<< orphan*/  dt_macros; TYPE_4__ dt_xlators; } ;
typedef  TYPE_3__ dtrace_hdl_t ;
typedef  TYPE_4__ dt_xlator_t ;
typedef  scalar_t__ dt_version_t ;
typedef  int /*<<< orphan*/  dt_idhash_f ;

/* Variables and functions */
 int DT_VERSION_STRMAX ; 
 int /*<<< orphan*/  EDT_VERSREDUCED ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_idhash_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_list_delete (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* dt_list_next (TYPE_4__*) ; 
 scalar_t__ dt_reduceid ; 
 int dt_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_version_num2str (scalar_t__,char*,int) ; 

int
dt_reduce(dtrace_hdl_t *dtp, dt_version_t v)
{
	char s[DT_VERSION_STRMAX];
	dt_xlator_t *dxp, *nxp;

	if (v > dtp->dt_vmax)
		return (dt_set_errno(dtp, EDT_VERSREDUCED));
	else if (v == dtp->dt_vmax)
		return (0); /* no reduction necessary */

	dt_dprintf("reducing api version to %s\n",
	    dt_version_num2str(v, s, sizeof (s)));

	dtp->dt_vmax = v;

	for (dxp = dt_list_next(&dtp->dt_xlators); dxp != NULL; dxp = nxp) {
		nxp = dt_list_next(dxp);
		if ((dxp->dx_souid.di_vers != 0 && dxp->dx_souid.di_vers > v) ||
		    (dxp->dx_ptrid.di_vers != 0 && dxp->dx_ptrid.di_vers > v))
			dt_list_delete(&dtp->dt_xlators, dxp);
	}

	(void) dt_idhash_iter(dtp->dt_macros, (dt_idhash_f *)dt_reduceid, dtp);
	(void) dt_idhash_iter(dtp->dt_aggs, (dt_idhash_f *)dt_reduceid, dtp);
	(void) dt_idhash_iter(dtp->dt_globals, (dt_idhash_f *)dt_reduceid, dtp);
	(void) dt_idhash_iter(dtp->dt_tls, (dt_idhash_f *)dt_reduceid, dtp);

	return (0);
}