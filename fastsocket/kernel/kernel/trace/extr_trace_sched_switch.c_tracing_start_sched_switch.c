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
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_ref ; 
 int /*<<< orphan*/  sched_register_mutex ; 
 int /*<<< orphan*/  tracing_sched_register () ; 

__attribute__((used)) static void tracing_start_sched_switch(void)
{
	mutex_lock(&sched_register_mutex);
	if (!(sched_ref++))
		tracing_sched_register();
	mutex_unlock(&sched_register_mutex);
}