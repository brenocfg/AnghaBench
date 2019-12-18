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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_tool {int dummy; } ;
struct machine {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;

/* Variables and functions */
 int perf_event__synthesize_comm (struct perf_tool*,union perf_event*,int,int,int /*<<< orphan*/ ,struct machine*) ; 
 int perf_event__synthesize_mmap_events (struct perf_tool*,union perf_event*,int,int,int /*<<< orphan*/ ,struct machine*) ; 

__attribute__((used)) static int __event__synthesize_thread(union perf_event *comm_event,
				      union perf_event *mmap_event,
				      pid_t pid, int full,
					  perf_event__handler_t process,
				      struct perf_tool *tool,
				      struct machine *machine)
{
	pid_t tgid = perf_event__synthesize_comm(tool, comm_event, pid, full,
						 process, machine);
	if (tgid == -1)
		return -1;
	return perf_event__synthesize_mmap_events(tool, mmap_event, pid, tgid,
						  process, machine);
}