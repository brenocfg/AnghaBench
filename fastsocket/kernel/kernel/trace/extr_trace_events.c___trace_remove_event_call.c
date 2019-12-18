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
struct ftrace_event_call {int /*<<< orphan*/  system; int /*<<< orphan*/  list; int /*<<< orphan*/  dir; scalar_t__ event; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unregister_ftrace_event (scalar_t__) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_preds (struct ftrace_event_call*) ; 
 int /*<<< orphan*/  ftrace_event_enable_disable (struct ftrace_event_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_subsystem_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_destroy_fields (struct ftrace_event_call*) ; 

__attribute__((used)) static void __trace_remove_event_call(struct ftrace_event_call *call)
{
	ftrace_event_enable_disable(call, 0);
	if (call->event)
		__unregister_ftrace_event(call->event);
	debugfs_remove_recursive(call->dir);
	list_del(&call->list);
	trace_destroy_fields(call);
	destroy_preds(call);
	remove_subsystem_dir(call->system);
}