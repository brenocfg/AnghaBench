#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int dtrd_action; scalar_t__ dtrd_offset; } ;
typedef  TYPE_2__ dtrace_recdesc_t ;
struct TYPE_7__ {int dtagd_nrecs; TYPE_2__* dtagd_rec; } ;
typedef  TYPE_3__ dtrace_aggdesc_t ;
struct TYPE_5__ {scalar_t__ dtada_data; TYPE_3__* dtada_desc; } ;
struct TYPE_8__ {TYPE_1__ dtahe_data; } ;
typedef  TYPE_4__ dt_ahashent_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  DTRACEAGG_AVG 136 
#define  DTRACEAGG_COUNT 135 
#define  DTRACEAGG_LLQUANTIZE 134 
#define  DTRACEAGG_LQUANTIZE 133 
#define  DTRACEAGG_MAX 132 
#define  DTRACEAGG_MIN 131 
#define  DTRACEAGG_QUANTIZE 130 
#define  DTRACEAGG_STDDEV 129 
#define  DTRACEAGG_SUM 128 
 int /*<<< orphan*/  assert (int) ; 
 int dt_aggregate_averagecmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_aggregate_countcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_aggregate_llquantizedcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_aggregate_lquantizedcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_aggregate_quantizedcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_aggregate_stddevcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dt_aggregate_valcmp(const void *lhs, const void *rhs)
{
	dt_ahashent_t *lh = *((dt_ahashent_t **)lhs);
	dt_ahashent_t *rh = *((dt_ahashent_t **)rhs);
	dtrace_aggdesc_t *lagg = lh->dtahe_data.dtada_desc;
	dtrace_aggdesc_t *ragg = rh->dtahe_data.dtada_desc;
	caddr_t ldata = lh->dtahe_data.dtada_data;
	caddr_t rdata = rh->dtahe_data.dtada_data;
	dtrace_recdesc_t *lrec, *rrec;
	int64_t *laddr, *raddr;
	int rval;

	assert(lagg->dtagd_nrecs == ragg->dtagd_nrecs);

	lrec = &lagg->dtagd_rec[lagg->dtagd_nrecs - 1];
	rrec = &ragg->dtagd_rec[ragg->dtagd_nrecs - 1];

	assert(lrec->dtrd_action == rrec->dtrd_action);

	laddr = (int64_t *)(uintptr_t)(ldata + lrec->dtrd_offset);
	raddr = (int64_t *)(uintptr_t)(rdata + rrec->dtrd_offset);

	switch (lrec->dtrd_action) {
	case DTRACEAGG_AVG:
		rval = dt_aggregate_averagecmp(laddr, raddr);
		break;

	case DTRACEAGG_STDDEV:
		rval = dt_aggregate_stddevcmp(laddr, raddr);
		break;

	case DTRACEAGG_QUANTIZE:
		rval = dt_aggregate_quantizedcmp(laddr, raddr);
		break;

	case DTRACEAGG_LQUANTIZE:
		rval = dt_aggregate_lquantizedcmp(laddr, raddr);
		break;

	case DTRACEAGG_LLQUANTIZE:
		rval = dt_aggregate_llquantizedcmp(laddr, raddr);
		break;

	case DTRACEAGG_COUNT:
	case DTRACEAGG_SUM:
	case DTRACEAGG_MIN:
	case DTRACEAGG_MAX:
		rval = dt_aggregate_countcmp(laddr, raddr);
		break;

	default:
		assert(0);
	}

	return (rval);
}