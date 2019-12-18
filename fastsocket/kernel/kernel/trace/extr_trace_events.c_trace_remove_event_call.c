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
struct ftrace_event_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_remove_event_call (struct ftrace_event_call*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_event_mutex ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void trace_remove_event_call(struct ftrace_event_call *call)
{
	mutex_lock(&event_mutex);
	down_write(&trace_event_mutex);
	__trace_remove_event_call(call);
	up_write(&trace_event_mutex);
	mutex_unlock(&event_mutex);
}