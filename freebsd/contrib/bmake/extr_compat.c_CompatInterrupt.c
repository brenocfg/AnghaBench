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
typedef  int /*<<< orphan*/  GNode ;

/* Variables and functions */
 int /*<<< orphan*/  CompatDeleteTarget (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Compat_Make (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KILLPG (scalar_t__,int) ; 
 int SIGINT ; 
 int SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  TARG_NOCREATE ; 
 int /*<<< orphan*/ * Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Targ_Precious (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  bmake_signal (int,int /*<<< orphan*/ ) ; 
 scalar_t__ compatChild ; 
 int compatSigno ; 
 int /*<<< orphan*/ * curTarg ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  myPid ; 

__attribute__((used)) static void
CompatInterrupt(int signo)
{
    GNode   *gn;

    CompatDeleteTarget(curTarg);

    if ((curTarg != NULL) && !Targ_Precious (curTarg)) {
	/*
	 * Run .INTERRUPT only if hit with interrupt signal
	 */
	if (signo == SIGINT) {
	    gn = Targ_FindNode(".INTERRUPT", TARG_NOCREATE);
	    if (gn != NULL) {
		Compat_Make(gn, gn);
	    }
	}
    }
    if (signo == SIGQUIT)
	_exit(signo);
    /*
     * If there is a child running, pass the signal on
     * we will exist after it has exited.
     */
    compatSigno = signo;
    if (compatChild > 0) {
	KILLPG(compatChild, signo);
    } else {
	bmake_signal(signo, SIG_DFL);
	kill(myPid, signo);
    }
}