#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobarg ;
struct TYPE_3__ {int inPipe; int outPipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  JobCreatePipe (TYPE_1__*,int) ; 
 int /*<<< orphan*/  JobTokenAdd () ; 
 int /*<<< orphan*/  MAKEFLAGS ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Append (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 TYPE_1__ tokenWaitJob ; 

void
Job_ServerStart(int max_tokens, int jp_0, int jp_1)
{
    int i;
    char jobarg[64];
    
    if (jp_0 >= 0 && jp_1 >= 0) {
	/* Pipe passed in from parent */
	tokenWaitJob.inPipe = jp_0;
	tokenWaitJob.outPipe = jp_1;
	(void)fcntl(jp_0, F_SETFD, FD_CLOEXEC);
	(void)fcntl(jp_1, F_SETFD, FD_CLOEXEC);
	return;
    }

    JobCreatePipe(&tokenWaitJob, 15);

    snprintf(jobarg, sizeof(jobarg), "%d,%d",
	    tokenWaitJob.inPipe, tokenWaitJob.outPipe);

    Var_Append(MAKEFLAGS, "-J", VAR_GLOBAL);
    Var_Append(MAKEFLAGS, jobarg, VAR_GLOBAL);			

    /*
     * Preload the job pipe with one token per job, save the one
     * "extra" token for the primary job.
     * 
     * XXX should clip maxJobs against PIPE_BUF -- if max_tokens is
     * larger than the write buffer size of the pipe, we will
     * deadlock here.
     */
    for (i = 1; i < max_tokens; i++)
	JobTokenAdd();
}