#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dtrace_aggvarid_t ;
struct TYPE_6__ {int dtagd_flags; scalar_t__ dtagd_nrecs; scalar_t__ dtagd_varid; } ;
typedef  TYPE_1__ dtrace_aggdesc_t ;
struct TYPE_7__ {TYPE_1__* dtada_desc; } ;
typedef  TYPE_2__ dtrace_aggdata_t ;
struct TYPE_8__ {scalar_t__ dtpa_id; scalar_t__ dtpa_allunprint; } ;
typedef  TYPE_3__ dt_print_aggdata_t ;

/* Variables and functions */
 int DTRACE_AGD_PRINTED ; 
 int dt_print_aggs (TYPE_2__ const**,int,void*) ; 

int
dt_print_agg(const dtrace_aggdata_t *aggdata, void *arg)
{
	dt_print_aggdata_t *pd = arg;
	dtrace_aggdesc_t *agg = aggdata->dtada_desc;
	dtrace_aggvarid_t aggvarid = pd->dtpa_id;

	if (pd->dtpa_allunprint) {
		if (agg->dtagd_flags & DTRACE_AGD_PRINTED)
			return (0);
	} else {
		/*
		 * If we're not printing all unprinted aggregations, then the
		 * aggregation variable ID denotes a specific aggregation
		 * variable that we should print -- skip any other aggregations
		 * that we encounter.
		 */
		if (agg->dtagd_nrecs == 0)
			return (0);

		if (aggvarid != agg->dtagd_varid)
			return (0);
	}

	return (dt_print_aggs(&aggdata, 1, arg));
}