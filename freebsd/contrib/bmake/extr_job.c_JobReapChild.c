#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  WAIT_T ;
struct TYPE_6__ {int pid; int job_suspended; int /*<<< orphan*/  exit_status; int /*<<< orphan*/  job_state; TYPE_1__* node; } ;
struct TYPE_5__ {char* name; } ;
typedef  TYPE_2__ Job ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB ; 
 int /*<<< orphan*/  JOB_ST_FINISHED ; 
 int /*<<< orphan*/  JOB_ST_RUNNING ; 
 TYPE_2__* JobFindPid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JobFinish (TYPE_2__*,int /*<<< orphan*/ ) ; 
#define  SIGSTOP 129 
#define  SIGTSTP 128 
 int /*<<< orphan*/  WAIT_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFSTOPPED (int /*<<< orphan*/ ) ; 
 int WSTOPSIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ jobTokensRunning ; 
 int /*<<< orphan*/  lurking_children ; 
 int /*<<< orphan*/  make_suspended ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

void
JobReapChild(pid_t pid, WAIT_T status, Boolean isJobs)
{
    Job		  *job;	    	/* job descriptor for dead child */

    /*
     * Don't even bother if we know there's no one around.
     */
    if (jobTokensRunning == 0)
	return;

    job = JobFindPid(pid, JOB_ST_RUNNING, isJobs);
    if (job == NULL) {
	if (isJobs) {
	    if (!lurking_children)
		Error("Child (%d) status %x not in table?", pid, status);
	}
	return;				/* not ours */
    }
    if (WIFSTOPPED(status)) {
	if (DEBUG(JOB)) {
	    (void)fprintf(debug_file, "Process %d (%s) stopped.\n",
			  job->pid, job->node->name);
	}
	if (!make_suspended) {
	    switch (WSTOPSIG(status)) {
	    case SIGTSTP:
		(void)printf("*** [%s] Suspended\n", job->node->name);
		break;
	    case SIGSTOP:
		(void)printf("*** [%s] Stopped\n", job->node->name);
		break;
	    default:
		(void)printf("*** [%s] Stopped -- signal %d\n",
			     job->node->name, WSTOPSIG(status));
	    }
	    job->job_suspended = 1;
	}
	(void)fflush(stdout);
	return;
    }

    job->job_state = JOB_ST_FINISHED;
    job->exit_status = WAIT_STATUS(status);

    JobFinish(job, status);
}