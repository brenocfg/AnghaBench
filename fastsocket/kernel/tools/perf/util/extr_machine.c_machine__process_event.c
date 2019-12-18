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
struct TYPE_2__ {int type; } ;
union perf_event {TYPE_1__ header; } ;
struct machine {int dummy; } ;

/* Variables and functions */
#define  PERF_RECORD_COMM 132 
#define  PERF_RECORD_EXIT 131 
#define  PERF_RECORD_FORK 130 
#define  PERF_RECORD_LOST 129 
#define  PERF_RECORD_MMAP 128 
 int machine__process_comm_event (struct machine*,union perf_event*) ; 
 int machine__process_exit_event (struct machine*,union perf_event*) ; 
 int machine__process_fork_event (struct machine*,union perf_event*) ; 
 int machine__process_lost_event (struct machine*,union perf_event*) ; 
 int machine__process_mmap_event (struct machine*,union perf_event*) ; 

int machine__process_event(struct machine *machine, union perf_event *event)
{
	int ret;

	switch (event->header.type) {
	case PERF_RECORD_COMM:
		ret = machine__process_comm_event(machine, event); break;
	case PERF_RECORD_MMAP:
		ret = machine__process_mmap_event(machine, event); break;
	case PERF_RECORD_FORK:
		ret = machine__process_fork_event(machine, event); break;
	case PERF_RECORD_EXIT:
		ret = machine__process_exit_event(machine, event); break;
	case PERF_RECORD_LOST:
		ret = machine__process_lost_event(machine, event); break;
	default:
		ret = -1;
		break;
	}

	return ret;
}