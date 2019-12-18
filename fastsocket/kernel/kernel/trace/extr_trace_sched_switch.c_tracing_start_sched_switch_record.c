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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ctx_trace ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_register_mutex ; 
 int /*<<< orphan*/  tracer_enabled ; 
 int /*<<< orphan*/  tracing_start_sched_switch () ; 
 scalar_t__ unlikely (int) ; 

void tracing_start_sched_switch_record(void)
{
	if (unlikely(!ctx_trace)) {
		WARN_ON(1);
		return;
	}

	tracing_start_sched_switch();

	mutex_lock(&sched_register_mutex);
	tracer_enabled++;
	mutex_unlock(&sched_register_mutex);
}