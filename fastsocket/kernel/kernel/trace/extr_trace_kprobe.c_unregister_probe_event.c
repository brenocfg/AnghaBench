#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  print_fmt; } ;
struct TYPE_4__ {TYPE_1__ fmt; } ;
struct trace_probe {TYPE_2__ call; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_remove_event_call (TYPE_2__*) ; 

__attribute__((used)) static void unregister_probe_event(struct trace_probe *tp)
{
	/* tp->event is unregistered in trace_remove_event_call() */
	trace_remove_event_call(&tp->call);
	kfree(tp->call.fmt.print_fmt);
}