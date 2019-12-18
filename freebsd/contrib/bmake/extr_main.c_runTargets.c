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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  Compat_Run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Job_Init () ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Make_Run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parse_MainName () ; 
 int /*<<< orphan*/  TARG_CREATE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Targ_FindList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compatMake ; 
 int /*<<< orphan*/  create ; 
 int /*<<< orphan*/  jobsRunning ; 
 int /*<<< orphan*/  queryFlag ; 

__attribute__((used)) static Boolean
runTargets(void)
{
	Lst targs;	/* target nodes to create -- passed to Make_Init */
	Boolean outOfDate; 	/* FALSE if all targets up to date */

	/*
	 * Have now read the entire graph and need to make a list of
	 * targets to create. If none was given on the command line,
	 * we consult the parsing module to find the main target(s)
	 * to create.
	 */
	if (Lst_IsEmpty(create))
		targs = Parse_MainName();
	else
		targs = Targ_FindList(create, TARG_CREATE);

	if (!compatMake) {
		/*
		 * Initialize job module before traversing the graph
		 * now that any .BEGIN and .END targets have been read.
		 * This is done only if the -q flag wasn't given
		 * (to prevent the .BEGIN from being executed should
		 * it exist).
		 */
		if (!queryFlag) {
			Job_Init();
			jobsRunning = TRUE;
		}

		/* Traverse the graph, checking on all the targets */
		outOfDate = Make_Run(targs);
	} else {
		/*
		 * Compat_Init will take care of creating all the
		 * targets as well as initializing the module.
		 */
		Compat_Run(targs);
		outOfDate = FALSE;
	}
	Lst_Destroy(targs, NULL);
	return outOfDate;
}