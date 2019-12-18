#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {uintptr_t ls_time; scalar_t__ ls_count; scalar_t__* ls_hist; } ;
typedef  TYPE_1__ lsrec_t ;
struct TYPE_10__ {scalar_t__ lsd_count; TYPE_1__* lsd_next; } ;
typedef  TYPE_2__ lsdata_t ;
struct TYPE_11__ {int dtrd_size; scalar_t__ dtrd_offset; } ;
typedef  TYPE_3__ dtrace_recdesc_t ;
struct TYPE_12__ {scalar_t__ dtagd_varid; int dtagd_nrecs; TYPE_3__* dtagd_rec; } ;
typedef  TYPE_4__ dtrace_aggdesc_t ;
struct TYPE_13__ {scalar_t__ dtada_data; TYPE_4__* dtada_desc; } ;
typedef  TYPE_5__ dtrace_aggdata_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ DTRACE_AGGVARIDNONE ; 
 int DTRACE_AGGWALK_NEXT ; 
 int DTRACE_QUANTIZE_NBUCKETS ; 
 int DTRACE_QUANTIZE_ZEROBUCKET ; 
 scalar_t__ LS_HIST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fail (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ g_nrecs ; 
 scalar_t__ g_recsize ; 
 int /*<<< orphan*/  lsrec_fill (TYPE_1__*,TYPE_3__*,int,scalar_t__) ; 

__attribute__((used)) static int
process_aggregate(const dtrace_aggdata_t *agg, void *arg)
{
	const dtrace_aggdesc_t *aggdesc = agg->dtada_desc;
	caddr_t data = agg->dtada_data;
	lsdata_t *lsdata = arg;
	lsrec_t *lsrec = lsdata->lsd_next;
	const dtrace_recdesc_t *rec;
	uint64_t *avg, *quantized;
	int i, j;

	assert(lsdata->lsd_count < g_nrecs);

	/*
	 * Aggregation variable IDs are guaranteed to be generated in program
	 * order, and they are guaranteed to start from DTRACE_AGGVARIDNONE
	 * plus one.  As "avg" appears before "hist" in program order, we know
	 * that "avg" will be allocated the first aggregation variable ID, and
	 * "hist" will be allocated the second aggregation variable ID -- and
	 * we therefore use the aggregation variable ID to differentiate the
	 * cases.
	 */
	if (aggdesc->dtagd_varid > DTRACE_AGGVARIDNONE + 1) {
		/*
		 * If this is the histogram entry.  We'll copy the quantized
		 * data into lc_hist, and jump over the rest.
		 */
		rec = &aggdesc->dtagd_rec[aggdesc->dtagd_nrecs - 1];

		if (aggdesc->dtagd_varid != DTRACE_AGGVARIDNONE + 2)
			fail(0, "bad variable ID in aggregation record");

		if (rec->dtrd_size !=
		    DTRACE_QUANTIZE_NBUCKETS * sizeof (uint64_t))
			fail(0, "bad quantize size in aggregation record");

		/* LINTED - alignment */
		quantized = (uint64_t *)(data + rec->dtrd_offset);

		for (i = DTRACE_QUANTIZE_ZEROBUCKET, j = 0;
		    i < DTRACE_QUANTIZE_NBUCKETS; i++, j++)
			lsrec->ls_hist[j] = quantized[i];

		goto out;
	}

	lsrec_fill(lsrec, &aggdesc->dtagd_rec[1],
	    aggdesc->dtagd_nrecs - 1, data);

	rec = &aggdesc->dtagd_rec[aggdesc->dtagd_nrecs - 1];

	if (rec->dtrd_size != 2 * sizeof (uint64_t))
		fail(0, "bad avg size in aggregation record");

	/* LINTED - alignment */
	avg = (uint64_t *)(data + rec->dtrd_offset);
	lsrec->ls_count = (uint32_t)avg[0];
	lsrec->ls_time = (uintptr_t)avg[1];

	if (g_recsize >= LS_HIST)
		return (DTRACE_AGGWALK_NEXT);

out:
	lsdata->lsd_next = (lsrec_t *)((uintptr_t)lsrec + g_recsize);
	lsdata->lsd_count++;

	return (DTRACE_AGGWALK_NEXT);
}