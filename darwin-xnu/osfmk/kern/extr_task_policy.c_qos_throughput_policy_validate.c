#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ task_throughput_qos_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ THROUGHPUT_QOS_TIER_0 ; 
 scalar_t__ THROUGHPUT_QOS_TIER_5 ; 
 scalar_t__ THROUGHPUT_QOS_TIER_UNSPECIFIED ; 

kern_return_t
qos_throughput_policy_validate(task_throughput_qos_t ttier) {
	if ((ttier != THROUGHPUT_QOS_TIER_UNSPECIFIED) &&
	    ((ttier > THROUGHPUT_QOS_TIER_5) || (ttier < THROUGHPUT_QOS_TIER_0)))
		return KERN_INVALID_ARGUMENT;

	return KERN_SUCCESS;
}