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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t thread_qos_t ;
struct TYPE_2__ {int /*<<< orphan*/ * qos_pri; } ;

/* Variables and functions */
 size_t THREAD_QOS_LAST ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ thread_qos_policy_params ; 

uint8_t
thread_workq_pri_for_qos(thread_qos_t qos)
{
	assert(qos < THREAD_QOS_LAST);
	return (uint8_t)thread_qos_policy_params.qos_pri[qos];
}