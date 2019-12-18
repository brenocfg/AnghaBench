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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  WAIT_T ;
struct TYPE_4__ {scalar_t__ job_state; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ERROR ; 
 scalar_t__ JOB_ST_RUNNING ; 
 int /*<<< orphan*/  KILLPG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  aborting ; 
 scalar_t__ jobTokensRunning ; 
 TYPE_1__* job_table ; 
 TYPE_1__* job_table_end ; 
 scalar_t__ waitpid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
Job_AbortAll(void)
{
    Job		*job;	/* the job descriptor in that element */
    WAIT_T	foo;

    aborting = ABORT_ERROR;

    if (jobTokensRunning) {
	for (job = job_table; job < job_table_end; job++) {
	    if (job->job_state != JOB_ST_RUNNING)
		continue;
	    /*
	     * kill the child process with increasingly drastic signals to make
	     * darn sure it's dead.
	     */
	    KILLPG(job->pid, SIGINT);
	    KILLPG(job->pid, SIGKILL);
	}
    }

    /*
     * Catch as many children as want to report in at first, then give up
     */
    while (waitpid((pid_t) -1, &foo, WNOHANG) > 0)
	continue;
}