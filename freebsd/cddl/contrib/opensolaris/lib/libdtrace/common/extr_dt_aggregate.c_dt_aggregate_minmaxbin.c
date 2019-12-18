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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_14__ {int dtrd_size; int dtrd_action; scalar_t__ dtrd_offset; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
struct TYPE_19__ {TYPE_5__* dtah_all; } ;
struct TYPE_20__ {TYPE_6__ dtat_hash; } ;
struct TYPE_15__ {TYPE_7__ dt_aggregate; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
typedef  int dtrace_aggid_t ;
struct TYPE_16__ {int dtagd_nrecs; size_t dtagd_varid; TYPE_1__* dtagd_rec; } ;
typedef  TYPE_3__ dtrace_aggdesc_t ;
struct TYPE_17__ {int dtada_minbin; int dtada_maxbin; int /*<<< orphan*/  dtada_flags; TYPE_3__* dtada_desc; scalar_t__ dtada_data; } ;
typedef  TYPE_4__ dtrace_aggdata_t ;
struct TYPE_18__ {TYPE_4__ dtahe_data; struct TYPE_18__* dtahe_nextall; } ;
typedef  TYPE_5__ dt_ahashent_t ;
typedef  TYPE_6__ dt_ahash_t ;
typedef  TYPE_7__ dt_aggregate_t ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  DTRACEAGG_LQUANTIZE 129 
#define  DTRACEAGG_QUANTIZE 128 
 int DTRACE_AGGVARIDNONE ; 
 int /*<<< orphan*/  DTRACE_A_MINMAXBIN ; 
 int DTRACE_QUANTIZE_ZEROBUCKET ; 
 int dt_aggregate_aggvarid (TYPE_5__*) ; 
 int /*<<< orphan*/  dt_free (TYPE_2__*,TYPE_4__**) ; 
 TYPE_4__** dt_zalloc (TYPE_2__*,int) ; 

__attribute__((used)) static int
dt_aggregate_minmaxbin(dtrace_hdl_t *dtp, boolean_t clear)
{
	dt_ahashent_t *h;
	dtrace_aggdata_t **minmax;
	dtrace_aggid_t max = DTRACE_AGGVARIDNONE, id;
	dt_aggregate_t *agp = &dtp->dt_aggregate;
	dt_ahash_t *hash = &agp->dtat_hash;

	for (h = hash->dtah_all; h != NULL; h = h->dtahe_nextall) {
		dtrace_aggdata_t *aggdata = &h->dtahe_data;

		if ((id = dt_aggregate_aggvarid(h)) > max)
			max = id;

		aggdata->dtada_minbin = 0;
		aggdata->dtada_maxbin = 0;
		aggdata->dtada_flags &= ~DTRACE_A_MINMAXBIN;
	}

	if (clear || max == DTRACE_AGGVARIDNONE)
		return (0);

	minmax = dt_zalloc(dtp, (max + 1) * sizeof (dtrace_aggdata_t *));

	if (minmax == NULL)
		return (-1);

	for (h = hash->dtah_all; h != NULL; h = h->dtahe_nextall) {
		dtrace_aggdata_t *aggdata = &h->dtahe_data;
		dtrace_aggdesc_t *agg = aggdata->dtada_desc;
		dtrace_recdesc_t *rec;
		caddr_t data;
		int64_t *addr;
		int minbin = -1, maxbin = -1, i;
		int start = 0, size;

		rec = &agg->dtagd_rec[agg->dtagd_nrecs - 1];
		size = rec->dtrd_size / sizeof (int64_t);
		data = aggdata->dtada_data;
		addr = (int64_t *)(uintptr_t)(data + rec->dtrd_offset);

		switch (rec->dtrd_action) {
		case DTRACEAGG_LQUANTIZE:
			/*
			 * For lquantize(), we always display the entire range
			 * of the aggregation when aggpack is set.
			 */
			start = 1;
			minbin = start;
			maxbin = size - 1 - start;
			break;

		case DTRACEAGG_QUANTIZE:
			for (i = start; i < size; i++) {
				if (!addr[i])
					continue;

				if (minbin == -1)
					minbin = i - start;

				maxbin = i - start;
			}

			if (minbin == -1) {
				/*
				 * If we have no data (e.g., due to a clear()
				 * or negative increments), we'll use the
				 * zero bucket as both our min and max.
				 */
				minbin = maxbin = DTRACE_QUANTIZE_ZEROBUCKET;
			}

			break;

		default:
			continue;
		}

		if (minmax[agg->dtagd_varid] == NULL) {
			minmax[agg->dtagd_varid] = aggdata;
			aggdata->dtada_flags |= DTRACE_A_MINMAXBIN;
			aggdata->dtada_minbin = minbin;
			aggdata->dtada_maxbin = maxbin;
			continue;
		}

		if (minbin < minmax[agg->dtagd_varid]->dtada_minbin)
			minmax[agg->dtagd_varid]->dtada_minbin = minbin;

		if (maxbin > minmax[agg->dtagd_varid]->dtada_maxbin)
			minmax[agg->dtagd_varid]->dtada_maxbin = maxbin;
	}

	/*
	 * And now one final pass to set everyone's minbin and maxbin.
	 */
	for (h = hash->dtah_all; h != NULL; h = h->dtahe_nextall) {
		dtrace_aggdata_t *aggdata = &h->dtahe_data, *mm;
		dtrace_aggdesc_t *agg = aggdata->dtada_desc;

		if ((mm = minmax[agg->dtagd_varid]) == NULL || aggdata == mm)
			continue;

		aggdata->dtada_minbin = mm->dtada_minbin;
		aggdata->dtada_maxbin = mm->dtada_maxbin;
		aggdata->dtada_flags |= DTRACE_A_MINMAXBIN;
	}

	dt_free(dtp, minmax);

	return (0);
}