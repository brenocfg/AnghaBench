#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int job_state; int pid; } ;
typedef  TYPE_1__ Job ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB ; 
 TYPE_1__* job_table ; 
 int /*<<< orphan*/  job_table_dump (char*) ; 
 TYPE_1__* job_table_end ; 

__attribute__((used)) static Job *
JobFindPid(int pid, int status, Boolean isJobs)
{
    Job *job;

    for (job = job_table; job < job_table_end; job++) {
	if ((job->job_state == status) && job->pid == pid)
	    return job;
    }
    if (DEBUG(JOB) && isJobs)
	job_table_dump("no pid");
    return NULL;
}