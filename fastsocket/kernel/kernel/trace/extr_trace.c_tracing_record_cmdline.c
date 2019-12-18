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
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_record_cmdline_disabled ; 
 int /*<<< orphan*/  trace_save_cmdline (struct task_struct*) ; 
 int /*<<< orphan*/  tracer_enabled ; 
 int /*<<< orphan*/  tracing_is_on () ; 

void tracing_record_cmdline(struct task_struct *tsk)
{
	if (atomic_read(&trace_record_cmdline_disabled) || !tracer_enabled ||
	    !tracing_is_on())
		return;

	trace_save_cmdline(tsk);
}