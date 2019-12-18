#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ made; } ;
typedef  TYPE_1__ GNode ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALLSRC ; 
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JobRun (TYPE_1__*) ; 
 int /*<<< orphan*/  PrintOnError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  TARG_NOCREATE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* Targ_FindNode (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var_Set (int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 

Boolean
Job_RunTarget(const char *target, const char *fname) {
    GNode *gn = Targ_FindNode(target, TARG_NOCREATE);

    if (gn == NULL)
	return FALSE;

    if (fname)
	Var_Set(ALLSRC, fname, gn, 0);

    JobRun(gn);
    if (gn->made == ERROR) {
	PrintOnError(gn, "\n\nStop.");
	exit(1);
    }
    return TRUE;
}