#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ made; char* name; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ ABORTED ; 
 scalar_t__ CompatInterrupt ; 
 int /*<<< orphan*/  Compat_Make (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* ENDNode ; 
 scalar_t__ ERROR ; 
 scalar_t__ Lst_DeQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Make_ExpandUse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_SPECIAL ; 
 int /*<<< orphan*/  PrintOnError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  Shell_Init () ; 
 int /*<<< orphan*/  TARG_CREATE ; 
 int /*<<< orphan*/  TARG_NOCREATE ; 
 TYPE_1__* Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ UPTODATE ; 
 scalar_t__ bmake_signal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  queryFlag ; 
 int /*<<< orphan*/  shellName ; 

void
Compat_Run(Lst targs)
{
    GNode   	  *gn = NULL;/* Current root target */
    int	    	  errors;   /* Number of targets not remade due to errors */

    if (!shellName)
	Shell_Init();

    if (bmake_signal(SIGINT, SIG_IGN) != SIG_IGN) {
	bmake_signal(SIGINT, CompatInterrupt);
    }
    if (bmake_signal(SIGTERM, SIG_IGN) != SIG_IGN) {
	bmake_signal(SIGTERM, CompatInterrupt);
    }
    if (bmake_signal(SIGHUP, SIG_IGN) != SIG_IGN) {
	bmake_signal(SIGHUP, CompatInterrupt);
    }
    if (bmake_signal(SIGQUIT, SIG_IGN) != SIG_IGN) {
	bmake_signal(SIGQUIT, CompatInterrupt);
    }

    ENDNode = Targ_FindNode(".END", TARG_CREATE);
    ENDNode->type = OP_SPECIAL;
    /*
     * If the user has defined a .BEGIN target, execute the commands attached
     * to it.
     */
    if (!queryFlag) {
	gn = Targ_FindNode(".BEGIN", TARG_NOCREATE);
	if (gn != NULL) {
	    Compat_Make(gn, gn);
            if (gn->made == ERROR) {
                PrintOnError(gn, "\nStop.");
                exit(1);
            }
	}
    }

    /*
     * Expand .USE nodes right now, because they can modify the structure
     * of the tree.
     */
    Make_ExpandUse(targs);

    /*
     * For each entry in the list of targets to create, call Compat_Make on
     * it to create the thing. Compat_Make will leave the 'made' field of gn
     * in one of several states:
     *	    UPTODATE	    gn was already up-to-date
     *	    MADE  	    gn was recreated successfully
     *	    ERROR 	    An error occurred while gn was being created
     *	    ABORTED	    gn was not remade because one of its inferiors
     *	    	  	    could not be made due to errors.
     */
    errors = 0;
    while (!Lst_IsEmpty (targs)) {
	gn = (GNode *)Lst_DeQueue(targs);
	Compat_Make(gn, gn);

	if (gn->made == UPTODATE) {
	    printf("`%s' is up to date.\n", gn->name);
	} else if (gn->made == ABORTED) {
	    printf("`%s' not remade because of errors.\n", gn->name);
	    errors += 1;
	}
    }

    /*
     * If the user has defined a .END target, run its commands.
     */
    if (errors == 0) {
	Compat_Make(ENDNode, ENDNode);
	if (gn->made == ERROR) {
	    PrintOnError(gn, "\nStop.");
	    exit(1);
	}
    }
}