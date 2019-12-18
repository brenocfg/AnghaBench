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
struct seq_file {int dummy; } ;
struct ftrace_event_call {int /*<<< orphan*/  name; int /*<<< orphan*/  system; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SYSTEM ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t_show(struct seq_file *m, void *v)
{
	struct ftrace_event_call *call = v;

	if (strcmp(call->system, TRACE_SYSTEM) != 0)
		seq_printf(m, "%s:", call->system);
	seq_printf(m, "%s\n", call->name);

	return 0;
}