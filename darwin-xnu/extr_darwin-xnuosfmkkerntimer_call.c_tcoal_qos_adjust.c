#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/ * latency_tier_rate_limited; int /*<<< orphan*/ * latency_qos_abstime_max; int /*<<< orphan*/ * latency_qos_scale; } ;
struct TYPE_5__ {scalar_t__ task; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NUM_LATENCY_QOS_TIERS ; 
 int /*<<< orphan*/  TASK_POLICY_LATENCY_QOS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int proc_get_effective_thread_policy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ tcoal_prio_params ; 

__attribute__((used)) static boolean_t tcoal_qos_adjust(thread_t t, int32_t *tshift, uint64_t *tmax_abstime, boolean_t *pratelimited) {
	uint32_t latency_qos;
	boolean_t adjusted = FALSE;
	task_t ctask = t->task;

	if (ctask) {
		latency_qos = proc_get_effective_thread_policy(t, TASK_POLICY_LATENCY_QOS);

		assert(latency_qos <= NUM_LATENCY_QOS_TIERS);

		if (latency_qos) {
			*tshift = tcoal_prio_params.latency_qos_scale[latency_qos - 1];
			*tmax_abstime = tcoal_prio_params.latency_qos_abstime_max[latency_qos - 1];
			*pratelimited = tcoal_prio_params.latency_tier_rate_limited[latency_qos - 1];
			adjusted = TRUE;
		}
	}
	return adjusted;
}