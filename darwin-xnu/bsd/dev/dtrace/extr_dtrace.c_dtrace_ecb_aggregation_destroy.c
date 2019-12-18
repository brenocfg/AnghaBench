#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__** dts_aggregations; int /*<<< orphan*/  dts_aggid_arena; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_9__ {TYPE_1__* dte_state; } ;
typedef  TYPE_2__ dtrace_ecb_t ;
struct TYPE_10__ {int dtag_id; } ;
typedef  TYPE_3__ dtrace_aggregation_t ;
typedef  int dtrace_aggid_t ;
struct TYPE_11__ {int /*<<< orphan*/  dta_kind; } ;
typedef  TYPE_4__ dtrace_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DTRACEACT_ISAGG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void
dtrace_ecb_aggregation_destroy(dtrace_ecb_t *ecb, dtrace_action_t *act)
{
	dtrace_aggregation_t *agg = (dtrace_aggregation_t *)act;
	dtrace_state_t *state = ecb->dte_state;
	dtrace_aggid_t aggid = agg->dtag_id;

	ASSERT(DTRACEACT_ISAGG(act->dta_kind));
	vmem_free(state->dts_aggid_arena, (void *)(uintptr_t)aggid, 1);

	ASSERT(state->dts_aggregations[aggid - 1] == agg);
	state->dts_aggregations[aggid - 1] = NULL;

	kmem_free(agg, sizeof (dtrace_aggregation_t));
}