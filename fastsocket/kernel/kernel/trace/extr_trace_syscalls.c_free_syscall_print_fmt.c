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
struct syscall_metadata {struct ftrace_event_call* enter_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  print_fmt; } ;
struct ftrace_event_call {TYPE_1__ fmt; struct syscall_metadata* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void free_syscall_print_fmt(struct ftrace_event_call *call)
{
	struct syscall_metadata *entry = call->data;

	if (entry->enter_event == call)
		kfree(call->fmt.print_fmt);
}