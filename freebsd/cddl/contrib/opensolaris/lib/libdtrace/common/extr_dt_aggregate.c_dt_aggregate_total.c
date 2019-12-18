#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_14__ {int dtrd_action; scalar_t__ dtrd_offset; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
struct TYPE_19__ {TYPE_5__* dtah_all; } ;
struct TYPE_20__ {TYPE_6__ dtat_hash; } ;
struct TYPE_15__ {scalar_t__* dt_options; TYPE_7__ dt_aggregate; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
typedef  int dtrace_aggid_t ;
struct TYPE_16__ {int dtagd_nrecs; size_t dtagd_varid; TYPE_1__* dtagd_rec; } ;
typedef  TYPE_3__ dtrace_aggdesc_t ;
struct TYPE_17__ {int dtada_total; int dtada_flags; TYPE_3__* dtada_desc; scalar_t__ dtada_data; } ;
typedef  TYPE_4__ dtrace_aggdata_t ;
struct TYPE_18__ {TYPE_4__ dtahe_data; struct TYPE_18__* dtahe_nextall; } ;
typedef  TYPE_5__ dt_ahashent_t ;
typedef  TYPE_6__ dt_ahash_t ;
typedef  TYPE_7__ dt_aggregate_t ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  DTRACEAGG_AVG 131 
#define  DTRACEAGG_COUNT 130 
#define  DTRACEAGG_STDDEV 129 
#define  DTRACEAGG_SUM 128 
 size_t DTRACEOPT_AGGZOOM ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 int DTRACE_AGGVARIDNONE ; 
 int DTRACE_AGGZOOM_MAX ; 
 int DTRACE_A_HASNEGATIVES ; 
 int DTRACE_A_HASPOSITIVES ; 
 int DTRACE_A_TOTAL ; 
 int dt_aggregate_aggvarid (TYPE_5__*) ; 
 int /*<<< orphan*/  dt_free (TYPE_2__*,TYPE_4__**) ; 
 int dt_stddev (int /*<<< orphan*/ *,int) ; 
 TYPE_4__** dt_zalloc (TYPE_2__*,int) ; 

__attribute__((used)) static int
dt_aggregate_total(dtrace_hdl_t *dtp, boolean_t clear)
{
	dt_ahashent_t *h;
	dtrace_aggdata_t **total;
	dtrace_aggid_t max = DTRACE_AGGVARIDNONE, id;
	dt_aggregate_t *agp = &dtp->dt_aggregate;
	dt_ahash_t *hash = &agp->dtat_hash;
	uint32_t tflags;

	tflags = DTRACE_A_TOTAL | DTRACE_A_HASNEGATIVES | DTRACE_A_HASPOSITIVES;

	/*
	 * If we need to deliver per-aggregation totals, we're going to take
	 * three passes over the aggregate:  one to clear everything out and
	 * determine our maximum aggregation ID, one to actually total
	 * everything up, and a final pass to assign the totals to the
	 * individual elements.
	 */
	for (h = hash->dtah_all; h != NULL; h = h->dtahe_nextall) {
		dtrace_aggdata_t *aggdata = &h->dtahe_data;

		if ((id = dt_aggregate_aggvarid(h)) > max)
			max = id;

		aggdata->dtada_total = 0;
		aggdata->dtada_flags &= ~tflags;
	}

	if (clear || max == DTRACE_AGGVARIDNONE)
		return (0);

	total = dt_zalloc(dtp, (max + 1) * sizeof (dtrace_aggdata_t *));

	if (total == NULL)
		return (-1);

	for (h = hash->dtah_all; h != NULL; h = h->dtahe_nextall) {
		dtrace_aggdata_t *aggdata = &h->dtahe_data;
		dtrace_aggdesc_t *agg = aggdata->dtada_desc;
		dtrace_recdesc_t *rec;
		caddr_t data;
		int64_t val, *addr;

		rec = &agg->dtagd_rec[agg->dtagd_nrecs - 1];
		data = aggdata->dtada_data;
		addr = (int64_t *)(uintptr_t)(data + rec->dtrd_offset);

		switch (rec->dtrd_action) {
		case DTRACEAGG_STDDEV:
			val = dt_stddev((uint64_t *)addr, 1);
			break;

		case DTRACEAGG_SUM:
		case DTRACEAGG_COUNT:
			val = *addr;
			break;

		case DTRACEAGG_AVG:
			val = addr[0] ? (addr[1] / addr[0]) : 0;
			break;

		default:
			continue;
		}

		if (total[agg->dtagd_varid] == NULL) {
			total[agg->dtagd_varid] = aggdata;
			aggdata->dtada_flags |= DTRACE_A_TOTAL;
		} else {
			aggdata = total[agg->dtagd_varid];
		}

		if (val > 0)
			aggdata->dtada_flags |= DTRACE_A_HASPOSITIVES;

		if (val < 0) {
			aggdata->dtada_flags |= DTRACE_A_HASNEGATIVES;
			val = -val;
		}

		if (dtp->dt_options[DTRACEOPT_AGGZOOM] != DTRACEOPT_UNSET) {
			val = (int64_t)((long double)val *
			    (1 / DTRACE_AGGZOOM_MAX));

			if (val > aggdata->dtada_total)
				aggdata->dtada_total = val;
		} else {
			aggdata->dtada_total += val;
		}
	}

	/*
	 * And now one final pass to set everyone's total.
	 */
	for (h = hash->dtah_all; h != NULL; h = h->dtahe_nextall) {
		dtrace_aggdata_t *aggdata = &h->dtahe_data, *t;
		dtrace_aggdesc_t *agg = aggdata->dtada_desc;

		if ((t = total[agg->dtagd_varid]) == NULL || aggdata == t)
			continue;

		aggdata->dtada_total = t->dtada_total;
		aggdata->dtada_flags |= (t->dtada_flags & tflags);
	}

	dt_free(dtp, total);

	return (0);
}