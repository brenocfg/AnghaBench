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
struct TYPE_2__ {int pid; int tid; int ppid; int ptid; } ;
union perf_event {TYPE_1__ fork; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*,int,int,int,int) ; 

size_t perf_event__fprintf_task(union perf_event *event, FILE *fp)
{
	return fprintf(fp, "(%d:%d):(%d:%d)\n",
		       event->fork.pid, event->fork.tid,
		       event->fork.ppid, event->fork.ptid);
}