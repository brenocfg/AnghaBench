#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
struct TYPE_9__ {int dt_errno; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_10__ {int /*<<< orphan*/  dtagd_flags; scalar_t__ dtagd_nrecs; int /*<<< orphan*/ * dtagd_rec; } ;
typedef  TYPE_2__ dtrace_aggdesc_t ;
struct TYPE_11__ {TYPE_2__* dtada_desc; int /*<<< orphan*/  dtada_size; int /*<<< orphan*/  dtada_data; } ;
typedef  TYPE_3__ dtrace_aggdata_t ;
struct TYPE_12__ {int pfw_err; TYPE_6__* pfw_argv; int /*<<< orphan*/  pfw_fp; } ;
typedef  TYPE_4__ dt_pfwalk_t ;
struct TYPE_13__ {TYPE_1__* pfv_dtp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_AGD_PRINTED ; 
 int dt_printf_format (TYPE_1__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const**,int) ; 

__attribute__((used)) static int
dt_fprintas(const dtrace_aggdata_t **aggsdata, int naggvars, void *arg)
{
	const dtrace_aggdata_t *aggdata = aggsdata[0];
	const dtrace_aggdesc_t *agg = aggdata->dtada_desc;
	const dtrace_recdesc_t *rec = &agg->dtagd_rec[1];
	uint_t nrecs = agg->dtagd_nrecs - 1;
	dt_pfwalk_t *pfw = arg;
	dtrace_hdl_t *dtp = pfw->pfw_argv->pfv_dtp;
	int i;

	if (dt_printf_format(dtp, pfw->pfw_fp, pfw->pfw_argv,
	    rec, nrecs, aggdata->dtada_data, aggdata->dtada_size,
	    aggsdata, naggvars) == -1)
		return (pfw->pfw_err = dtp->dt_errno);

	/*
	 * For each aggregation, indicate that it has been printed, casting
	 * away the const as necessary.
	 */
	for (i = 1; i < naggvars; i++) {
		agg = aggsdata[i]->dtada_desc;
		((dtrace_aggdesc_t *)agg)->dtagd_flags |= DTRACE_AGD_PRINTED;
	}

	return (0);
}