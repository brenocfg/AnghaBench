#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int job_state; int flags; int pid; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* job_table ; 
 TYPE_1__* job_table_end ; 

__attribute__((used)) static void
job_table_dump(const char *where)
{
    Job *job;

    fprintf(debug_file, "job table @ %s\n", where);
    for (job = job_table; job < job_table_end; job++) {
	fprintf(debug_file, "job %d, status %d, flags %d, pid %d\n",
	    (int)(job - job_table), job->job_state, job->flags, job->pid);
    }
}