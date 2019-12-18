#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dts_naggregations; TYPE_2__** dts_aggregations; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_6__ {int dtag_id; } ;
typedef  TYPE_2__ dtrace_aggregation_t ;
typedef  int dtrace_aggid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_lock ; 

__attribute__((used)) static dtrace_aggregation_t *
dtrace_aggid2agg(dtrace_state_t *state, dtrace_aggid_t id)
{
	dtrace_aggregation_t *agg;
#pragma unused(agg) /* __APPLE__ */

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	if (id == 0 || id > (dtrace_aggid_t)state->dts_naggregations)
		return (NULL);

	ASSERT(state->dts_naggregations > 0 && state->dts_aggregations != NULL);
	ASSERT((agg = state->dts_aggregations[id - 1]) == NULL ||
	    agg->dtag_id == id);

	return (state->dts_aggregations[id - 1]);
}