#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
struct TYPE_3__ {int /*<<< orphan*/  _a_prio; } ;
typedef  TYPE_1__ pthread_attr_t ;

/* Variables and functions */

int pthread_attr_setschedparam(pthread_attr_t *restrict a, const struct sched_param *restrict param)
{
	a->_a_prio = param->sched_priority;
	return 0;
}