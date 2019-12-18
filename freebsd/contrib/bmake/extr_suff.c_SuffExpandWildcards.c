#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parents; int /*<<< orphan*/  children; int /*<<< orphan*/  unmade; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Dir_Expand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Dir_HasWildcards (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_DeQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_InsertBefore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Member (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  Suff_FindPath (TYPE_1__*) ; 
 int /*<<< orphan*/  TARG_CREATE ; 
 TYPE_1__* Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
SuffExpandWildcards(LstNode cln, GNode *pgn)
{
    GNode   	*cgn = (GNode *)Lst_Datum(cln);
    GNode	*gn;	    /* New source 8) */
    char	*cp;	    /* Expanded value */
    Lst 	explist;    /* List of expansions */

    if (!Dir_HasWildcards(cgn->name))
	return;

    /*
     * Expand the word along the chosen path
     */
    explist = Lst_Init(FALSE);
    Dir_Expand(cgn->name, Suff_FindPath(cgn), explist);

    while (!Lst_IsEmpty(explist)) {
	/*
	 * Fetch next expansion off the list and find its GNode
	 */
	cp = (char *)Lst_DeQueue(explist);

	if (DEBUG(SUFF)) {
	    fprintf(debug_file, "%s...", cp);
	}
	gn = Targ_FindNode(cp, TARG_CREATE);

	/* Add gn to the parents child list before the original child */
	(void)Lst_InsertBefore(pgn->children, cln, gn);
	(void)Lst_AtEnd(gn->parents, pgn);
	pgn->unmade++;
    }

    /*
     * Nuke what's left of the list
     */
    Lst_Destroy(explist, NULL);

    if (DEBUG(SUFF)) {
	fprintf(debug_file, "\n");
    }

    /*
     * Now the source is expanded, remove it from the list of children to
     * keep it from being processed.
     */
    pgn->unmade--;
    Lst_Remove(pgn->children, cln);
    Lst_Remove(cgn->parents, Lst_Member(cgn->parents, pgn));
}