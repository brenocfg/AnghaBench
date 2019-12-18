#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_11__ {size_t dtrd_size; scalar_t__ dtrd_offset; int /*<<< orphan*/  dtrd_action; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_12__ {int dtagd_nrecs; int /*<<< orphan*/  dtagd_flags; TYPE_1__* dtagd_rec; } ;
typedef  TYPE_2__ dtrace_aggdesc_t ;
struct TYPE_13__ {int dtada_flags; int dtada_normal; scalar_t__ dtada_data; TYPE_2__* dtada_desc; } ;
typedef  TYPE_3__ dtrace_aggdata_t ;
typedef  int /*<<< orphan*/  dtrace_actkind_t ;
struct TYPE_14__ {int dtpa_agghist; int dtpa_aggpack; int /*<<< orphan*/  dtpa_allunprint; int /*<<< orphan*/ * dtpa_dtp; int /*<<< orphan*/ * dtpa_fp; } ;
typedef  TYPE_4__ dt_print_aggdata_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DTRACEACT_ISAGG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_AGD_PRINTED ; 
 int DTRACE_A_MINMAXBIN ; 
 int DTRACE_A_TOTAL ; 
 int DTRACE_BUFDATA_AGGFORMAT ; 
 int DTRACE_BUFDATA_AGGKEY ; 
 int DTRACE_BUFDATA_AGGLAST ; 
 int DTRACE_BUFDATA_AGGVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dt_buffered_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int) ; 
 scalar_t__ dt_print_datum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,size_t,TYPE_3__ const*,int,TYPE_4__*) ; 
 scalar_t__ dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int
dt_print_aggs(const dtrace_aggdata_t **aggsdata, int naggvars, void *arg)
{
	int i, aggact = 0;
	dt_print_aggdata_t *pd = arg;
	const dtrace_aggdata_t *aggdata = aggsdata[0];
	dtrace_aggdesc_t *agg = aggdata->dtada_desc;
	FILE *fp = pd->dtpa_fp;
	dtrace_hdl_t *dtp = pd->dtpa_dtp;
	dtrace_recdesc_t *rec;
	dtrace_actkind_t act;
	caddr_t addr;
	size_t size;

	pd->dtpa_agghist = (aggdata->dtada_flags & DTRACE_A_TOTAL);
	pd->dtpa_aggpack = (aggdata->dtada_flags & DTRACE_A_MINMAXBIN);

	/*
	 * Iterate over each record description in the key, printing the traced
	 * data, skipping the first datum (the tuple member created by the
	 * compiler).
	 */
	for (i = 1; i < agg->dtagd_nrecs; i++) {
		rec = &agg->dtagd_rec[i];
		act = rec->dtrd_action;
		addr = aggdata->dtada_data + rec->dtrd_offset;
		size = rec->dtrd_size;

		if (DTRACEACT_ISAGG(act)) {
			aggact = i;
			break;
		}

		if (dt_print_datum(dtp, fp, rec, addr,
		    size, aggdata, 1, pd) < 0)
			return (-1);

		if (dt_buffered_flush(dtp, NULL, rec, aggdata,
		    DTRACE_BUFDATA_AGGKEY) < 0)
			return (-1);
	}

	assert(aggact != 0);

	for (i = (naggvars == 1 ? 0 : 1); i < naggvars; i++) {
		uint64_t normal;

		aggdata = aggsdata[i];
		agg = aggdata->dtada_desc;
		rec = &agg->dtagd_rec[aggact];
		act = rec->dtrd_action;
		addr = aggdata->dtada_data + rec->dtrd_offset;
		size = rec->dtrd_size;

		assert(DTRACEACT_ISAGG(act));
		normal = aggdata->dtada_normal;

		if (dt_print_datum(dtp, fp, rec, addr,
		    size, aggdata, normal, pd) < 0)
			return (-1);

		if (dt_buffered_flush(dtp, NULL, rec, aggdata,
		    DTRACE_BUFDATA_AGGVAL) < 0)
			return (-1);

		if (!pd->dtpa_allunprint)
			agg->dtagd_flags |= DTRACE_AGD_PRINTED;
	}

	if (!pd->dtpa_agghist && !pd->dtpa_aggpack) {
		if (dt_printf(dtp, fp, "\n") < 0)
			return (-1);
	}

	if (dt_buffered_flush(dtp, NULL, NULL, aggdata,
	    DTRACE_BUFDATA_AGGFORMAT | DTRACE_BUFDATA_AGGLAST) < 0)
		return (-1);

	return (0);
}