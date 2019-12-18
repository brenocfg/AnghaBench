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
struct TYPE_2__ {char* comm; int tid; } ;
union perf_event {TYPE_1__ comm; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*,char*,int) ; 

size_t perf_event__fprintf_comm(union perf_event *event, FILE *fp)
{
	return fprintf(fp, ": %s:%d\n", event->comm.comm, event->comm.tid);
}