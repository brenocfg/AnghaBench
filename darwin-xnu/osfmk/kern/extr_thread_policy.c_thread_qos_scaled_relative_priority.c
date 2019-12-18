#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* qos_pri; } ;

/* Variables and functions */
#define  THREAD_QOS_BACKGROUND 133 
#define  THREAD_QOS_LEGACY 132 
#define  THREAD_QOS_MAINTENANCE 131 
#define  THREAD_QOS_USER_INITIATED 130 
#define  THREAD_QOS_USER_INTERACTIVE 129 
#define  THREAD_QOS_UTILITY 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_1__ thread_qos_policy_params ; 

__attribute__((used)) static int
thread_qos_scaled_relative_priority(int qos, int qos_relprio)
{
	int next_lower_qos;

	/* Fast path, since no validation or scaling is needed */
	if (qos_relprio == 0) return 0;

	switch (qos) {
		case THREAD_QOS_USER_INTERACTIVE:
			next_lower_qos = THREAD_QOS_USER_INITIATED;
			break;
		case THREAD_QOS_USER_INITIATED:
			next_lower_qos = THREAD_QOS_LEGACY;
			break;
		case THREAD_QOS_LEGACY:
			next_lower_qos = THREAD_QOS_UTILITY;
			break;
		case THREAD_QOS_UTILITY:
			next_lower_qos = THREAD_QOS_BACKGROUND;
			break;
		case THREAD_QOS_MAINTENANCE:
		case THREAD_QOS_BACKGROUND:
			next_lower_qos = 0;
			break;
		default:
			panic("Unrecognized QoS %d", qos);
			return 0;
	}

	int prio_range_max = thread_qos_policy_params.qos_pri[qos];
	int prio_range_min = next_lower_qos ? thread_qos_policy_params.qos_pri[next_lower_qos] : 0;

	/*
	 * We now have the valid range that the scaled relative priority can map to. Note
	 * that the lower bound is exclusive, but the upper bound is inclusive. If the
	 * range is (21,31], 0REL should map to 31 and -15REL should map to 22. We use the
	 * fact that the max relative priority is -15 and use ">>4" to divide by 16 and discard
	 * remainder.
	 */
	int scaled_relprio = -(((prio_range_max - prio_range_min) * (-qos_relprio)) >> 4);

	return scaled_relprio;
}