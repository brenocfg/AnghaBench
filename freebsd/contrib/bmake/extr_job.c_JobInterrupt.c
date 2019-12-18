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
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {scalar_t__ job_state; int pid; int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ Job ;
typedef  int /*<<< orphan*/  GNode ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_INTERRUPT ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JOB ; 
 scalar_t__ JOB_ST_RUNNING ; 
 int /*<<< orphan*/  JobDeleteTarget (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JobRun (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JobSigLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JobSigUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KILLPG (int,int) ; 
 int /*<<< orphan*/  MAKEINTR ; 
 int /*<<< orphan*/  TARG_NOCREATE ; 
 int /*<<< orphan*/ * Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Trace_Log (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aborting ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ignoreErrors ; 
 TYPE_1__* job_table ; 
 TYPE_1__* job_table_end ; 
 int /*<<< orphan*/  touchFlag ; 

__attribute__((used)) static void
JobInterrupt(int runINTERRUPT, int signo)
{
    Job		*job;		/* job descriptor in that element */
    GNode	*interrupt;	/* the node describing the .INTERRUPT target */
    sigset_t	mask;
    GNode	*gn;

    aborting = ABORT_INTERRUPT;

    JobSigLock(&mask);

    for (job = job_table; job < job_table_end; job++) {
	if (job->job_state != JOB_ST_RUNNING)
	    continue;

	gn = job->node;

	JobDeleteTarget(gn);
	if (job->pid) {
	    if (DEBUG(JOB)) {
		(void)fprintf(debug_file,
			   "JobInterrupt passing signal %d to child %d.\n",
			   signo, job->pid);
	    }
	    KILLPG(job->pid, signo);
	}
    }

    JobSigUnlock(&mask);

    if (runINTERRUPT && !touchFlag) {
	interrupt = Targ_FindNode(".INTERRUPT", TARG_NOCREATE);
	if (interrupt != NULL) {
	    ignoreErrors = FALSE;
	    JobRun(interrupt);
	}
    }
    Trace_Log(MAKEINTR, 0);
    exit(signo);
}