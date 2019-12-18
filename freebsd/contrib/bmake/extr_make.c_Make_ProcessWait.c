#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; int type; char* name; int /*<<< orphan*/  children; int /*<<< orphan*/  cohorts; } ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int DONE_WAIT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LST_CONCLINK ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_AtFront (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* Lst_Datum (int /*<<< orphan*/ *) ; 
 TYPE_1__* Lst_DeQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_First (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_ForEachFrom (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE ; 
 int /*<<< orphan*/  MakeBuildChild (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int OP_DEPENDS ; 
 int OP_DOUBLEDEP ; 
 int OP_PHONY ; 
 int OP_WAIT ; 
 int REMAKE ; 
 int /*<<< orphan*/  Targ_List () ; 
 TYPE_1__* Targ_NewGN (char*) ; 
 int /*<<< orphan*/  add_wait_dep ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  link_parent ; 

__attribute__((used)) static void
Make_ProcessWait(Lst targs)
{
    GNode  *pgn;	/* 'parent' node we are examining */
    GNode  *cgn;	/* Each child in turn */
    LstNode owln;	/* Previous .WAIT node */
    Lst    examine; 	/* List of targets to examine */
    LstNode ln;

    /*
     * We need all the nodes to have a common parent in order for the
     * .WAIT and .ORDER scheduling to work.
     * Perhaps this should be done earlier...
     */

    pgn = Targ_NewGN(".MAIN");
    pgn->flags = REMAKE;
    pgn->type = OP_PHONY | OP_DEPENDS;
    /* Get it displayed in the diag dumps */
    Lst_AtFront(Targ_List(), pgn);

    Lst_ForEach(targs, link_parent, pgn);

    /* Start building with the 'dummy' .MAIN' node */
    MakeBuildChild(pgn, NULL);

    examine = Lst_Init(FALSE);
    Lst_AtEnd(examine, pgn);

    while (!Lst_IsEmpty (examine)) {
	pgn = Lst_DeQueue(examine);
   
	/* We only want to process each child-list once */
	if (pgn->flags & DONE_WAIT)
	    continue;
	pgn->flags |= DONE_WAIT;
	if (DEBUG(MAKE))
	    fprintf(debug_file, "Make_ProcessWait: examine %s\n", pgn->name);

	if ((pgn->type & OP_DOUBLEDEP) && !Lst_IsEmpty (pgn->cohorts)) {
	    /* Append all the 'cohorts' to the list of things to examine */
	    Lst new;
	    new = Lst_Duplicate(pgn->cohorts, NULL);
	    Lst_Concat(new, examine, LST_CONCLINK);
	    examine = new;
	}

	owln = Lst_First(pgn->children);
	Lst_Open(pgn->children);
	for (; (ln = Lst_Next(pgn->children)) != NULL; ) {
	    cgn = Lst_Datum(ln);
	    if (cgn->type & OP_WAIT) {
		/* Make the .WAIT node depend on the previous children */
		Lst_ForEachFrom(pgn->children, owln, add_wait_dep, cgn);
		owln = ln;
	    } else {
		Lst_AtEnd(examine, cgn);
	    }
	}
	Lst_Close(pgn->children);
    }

    Lst_Destroy(examine, NULL);
}