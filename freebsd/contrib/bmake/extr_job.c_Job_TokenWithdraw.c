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
struct TYPE_2__ {int /*<<< orphan*/  outPipe; int /*<<< orphan*/  inPipe; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Fatal (char*,...) ; 
 int /*<<< orphan*/  JOB ; 
 int /*<<< orphan*/  TRUE ; 
 int aborting ; 
 int /*<<< orphan*/  debug_file ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int getpid () ; 
 int jobTokensRunning ; 
 int maxJobs ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 TYPE_1__ tokenWaitJob ; 
 scalar_t__ wantToken ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

Boolean
Job_TokenWithdraw(void)
{
    char tok, tok1;
    int count;

    wantToken = 0;
    if (DEBUG(JOB))
	fprintf(debug_file, "Job_TokenWithdraw(%d): aborting %d, running %d\n",
		getpid(), aborting, jobTokensRunning);

    if (aborting || (jobTokensRunning >= maxJobs))
	return FALSE;

    count = read(tokenWaitJob.inPipe, &tok, 1);
    if (count == 0)
	Fatal("eof on job pipe!");
    if (count < 0 && jobTokensRunning != 0) {
	if (errno != EAGAIN) {
	    Fatal("job pipe read: %s", strerror(errno));
	}
	if (DEBUG(JOB))
	    fprintf(debug_file, "(%d) blocked for token\n", getpid());
	return FALSE;
    }

    if (count == 1 && tok != '+') {
	/* make being abvorted - remove any other job tokens */
	if (DEBUG(JOB))
	    fprintf(debug_file, "(%d) aborted by token %c\n", getpid(), tok);
	while (read(tokenWaitJob.inPipe, &tok1, 1) == 1)
	    continue;
	/* And put the stopper back */
	while (write(tokenWaitJob.outPipe, &tok, 1) == -1 && errno == EAGAIN)
	    continue;
	Fatal("A failure has been detected in another branch of the parallel make");
    }

    if (count == 1 && jobTokensRunning == 0)
	/* We didn't want the token really */
	while (write(tokenWaitJob.outPipe, &tok, 1) == -1 && errno == EAGAIN)
	    continue;

    jobTokensRunning++;
    if (DEBUG(JOB))
	fprintf(debug_file, "(%d) withdrew token\n", getpid());
    return TRUE;
}