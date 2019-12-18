#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Lst ;
typedef  int Boolean ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Job_CatchOutput () ; 
 int Job_Finish () ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE ; 
 int /*<<< orphan*/  MakePrintStatus ; 
 int MakeStartJobs () ; 
 int /*<<< orphan*/  Make_ExpandUse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Make_ProcessWait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Targ_PrintGraph (int) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ jobTokensRunning ; 
 scalar_t__ queryFlag ; 
 int /*<<< orphan*/  toBeMade ; 

Boolean
Make_Run(Lst targs)
{
    int	    	    errors; 	/* Number of errors the Job module reports */

    /* Start trying to make the current targets... */
    toBeMade = Lst_Init(FALSE);

    Make_ExpandUse(targs);
    Make_ProcessWait(targs);

    if (DEBUG(MAKE)) {
	 fprintf(debug_file, "#***# full graph\n");
	 Targ_PrintGraph(1);
    }

    if (queryFlag) {
	/*
	 * We wouldn't do any work unless we could start some jobs in the
	 * next loop... (we won't actually start any, of course, this is just
	 * to see if any of the targets was out of date)
	 */
	return (MakeStartJobs());
    }
    /*
     * Initialization. At the moment, no jobs are running and until some
     * get started, nothing will happen since the remaining upward
     * traversal of the graph is performed by the routines in job.c upon
     * the finishing of a job. So we fill the Job table as much as we can
     * before going into our loop.
     */
    (void)MakeStartJobs();

    /*
     * Main Loop: The idea here is that the ending of jobs will take
     * care of the maintenance of data structures and the waiting for output
     * will cause us to be idle most of the time while our children run as
     * much as possible. Because the job table is kept as full as possible,
     * the only time when it will be empty is when all the jobs which need
     * running have been run, so that is the end condition of this loop.
     * Note that the Job module will exit if there were any errors unless the
     * keepgoing flag was given.
     */
    while (!Lst_IsEmpty(toBeMade) || jobTokensRunning > 0) {
	Job_CatchOutput();
	(void)MakeStartJobs();
    }

    errors = Job_Finish();

    /*
     * Print the final status of each target. E.g. if it wasn't made
     * because some inferior reported an error.
     */
    if (DEBUG(MAKE))
	 fprintf(debug_file, "done: errors %d\n", errors);
    if (errors == 0) {
	Lst_ForEach(targs, MakePrintStatus, &errors);
	if (DEBUG(MAKE)) {
	    fprintf(debug_file, "done: errors %d\n", errors);
	    if (errors)
		Targ_PrintGraph(4);
	}
    }
    return errors != 0;
}