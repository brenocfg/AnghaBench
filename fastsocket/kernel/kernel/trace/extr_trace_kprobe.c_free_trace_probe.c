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
struct TYPE_2__ {struct trace_probe* name; struct trace_probe* system; } ;
struct trace_probe {int nr_args; struct trace_probe* symbol; TYPE_1__ call; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_probe_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct trace_probe*) ; 

__attribute__((used)) static void free_trace_probe(struct trace_probe *tp)
{
	int i;

	for (i = 0; i < tp->nr_args; i++)
		free_probe_arg(&tp->args[i]);

	kfree(tp->call.system);
	kfree(tp->call.name);
	kfree(tp->symbol);
	kfree(tp);
}