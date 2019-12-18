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
typedef  int uint_t ;
struct TYPE_6__ {scalar_t__ dtrd_uarg; scalar_t__ dtrd_action; scalar_t__ dtrd_offset; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_probedata_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_aggvarid_t ;
struct TYPE_7__ {scalar_t__ pfw_err; int /*<<< orphan*/  pfw_aid; int /*<<< orphan*/ * pfw_fp; void* pfw_argv; } ;
typedef  TYPE_2__ dt_pfwalk_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADAGG ; 
 int /*<<< orphan*/ * alloca (int) ; 
 int /*<<< orphan*/  dt_fprinta ; 
 int /*<<< orphan*/  dt_fprintas ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dtrace_aggregate_walk_joined (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int dtrace_aggregate_walk_sorted (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

int
dtrace_fprinta(dtrace_hdl_t *dtp, FILE *fp, void *fmtdata,
    const dtrace_probedata_t *data, const dtrace_recdesc_t *recs,
    uint_t nrecs, const void *buf, size_t len)
{
	dt_pfwalk_t pfw;
	int i, naggvars = 0;
	dtrace_aggvarid_t *aggvars;

	aggvars = alloca(nrecs * sizeof (dtrace_aggvarid_t));

	/*
	 * This might be a printa() with multiple aggregation variables.  We
	 * need to scan forward through the records until we find a record from
	 * a different statement.
	 */
	for (i = 0; i < nrecs; i++) {
		const dtrace_recdesc_t *nrec = &recs[i];

		if (nrec->dtrd_uarg != recs->dtrd_uarg)
			break;

		if (nrec->dtrd_action != recs->dtrd_action)
			return (dt_set_errno(dtp, EDT_BADAGG));

		aggvars[naggvars++] =
		    /* LINTED - alignment */
		    *((dtrace_aggvarid_t *)((caddr_t)buf + nrec->dtrd_offset));
	}

	if (naggvars == 0)
		return (dt_set_errno(dtp, EDT_BADAGG));

	pfw.pfw_argv = fmtdata;
	pfw.pfw_fp = fp;
	pfw.pfw_err = 0;

	if (naggvars == 1) {
		pfw.pfw_aid = aggvars[0];

		if (dtrace_aggregate_walk_sorted(dtp,
		    dt_fprinta, &pfw) == -1 || pfw.pfw_err != 0)
			return (-1); /* errno is set for us */
	} else {
		if (dtrace_aggregate_walk_joined(dtp, aggvars, naggvars,
		    dt_fprintas, &pfw) == -1 || pfw.pfw_err != 0)
			return (-1); /* errno is set for us */
	}

	return (i);
}