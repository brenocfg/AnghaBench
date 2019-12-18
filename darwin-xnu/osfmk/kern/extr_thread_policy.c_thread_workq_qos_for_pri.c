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
typedef  int thread_qos_t ;
struct TYPE_2__ {int* qos_pri; } ;

/* Variables and functions */
 int THREAD_QOS_MAINTENANCE ; 
 int THREAD_QOS_UNSPECIFIED ; 
 size_t THREAD_QOS_USER_INTERACTIVE ; 
 TYPE_1__ thread_qos_policy_params ; 

thread_qos_t
thread_workq_qos_for_pri(int priority)
{
	int qos;
	if (priority > thread_qos_policy_params.qos_pri[THREAD_QOS_USER_INTERACTIVE]) {
		// indicate that workq should map >UI threads to workq's
		// internal notation for above-UI work.
		return THREAD_QOS_UNSPECIFIED;
	}
	for (qos = THREAD_QOS_USER_INTERACTIVE; qos > THREAD_QOS_MAINTENANCE; qos--) {
		// map a given priority up to the next nearest qos band.
		if (thread_qos_policy_params.qos_pri[qos - 1] < priority) {
			return qos;
		}
	}
	return THREAD_QOS_MAINTENANCE;
}