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
struct trace_seq {int dummy; } ;
struct trace_entry {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  trace_find_cmdline (int /*<<< orphan*/ ,char*) ; 
 int trace_print_lat_fmt (struct trace_seq*,struct trace_entry*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lat_print_generic(struct trace_seq *s, struct trace_entry *entry, int cpu)
{
	char comm[TASK_COMM_LEN];

	trace_find_cmdline(entry->pid, comm);

	if (!trace_seq_printf(s, "%8.8s-%-5d %3d",
			      comm, entry->pid, cpu))
		return 0;

	return trace_print_lat_fmt(s, entry);
}