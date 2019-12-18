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
struct TYPE_4__ {scalar_t__ job_state; int pid; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB ; 
 scalar_t__ JOB_ST_RUNNING ; 
 int /*<<< orphan*/  KILLPG (int,int) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_1__* job_table ; 
 TYPE_1__* job_table_end ; 

__attribute__((used)) static void
JobCondPassSig(int signo)
{
    Job *job;

    if (DEBUG(JOB)) {
	(void)fprintf(debug_file, "JobCondPassSig(%d) called.\n", signo);
    }

    for (job = job_table; job < job_table_end; job++) {
	if (job->job_state != JOB_ST_RUNNING)
	    continue;
	if (DEBUG(JOB)) {
	    (void)fprintf(debug_file,
			   "JobCondPassSig passing signal %d to child %d.\n",
			   signo, job->pid);
	}
	KILLPG(job->pid, signo);
    }
}