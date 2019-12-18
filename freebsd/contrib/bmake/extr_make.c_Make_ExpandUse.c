#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int flags; char* name; int cohort_num; int type; char* path; scalar_t__ unmade; int /*<<< orphan*/  children; struct TYPE_15__* cohorts; } ;
typedef  TYPE_1__* Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Dir_MTime (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LST_CONCLINK ; 
 int /*<<< orphan*/  Lst_Concat (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_DeQueue (TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Destroy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* Lst_Duplicate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_IsEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  MAKE ; 
 int /*<<< orphan*/  MEMBER ; 
 int /*<<< orphan*/  MakeAddChild ; 
 int /*<<< orphan*/  MakeFindChild ; 
 int /*<<< orphan*/  MakeHandleUse ; 
 int /*<<< orphan*/  MakeUnmark ; 
 int OP_ARCHV ; 
 int OP_DOUBLEDEP ; 
 int OP_MADE ; 
 int REMAKE ; 
 int /*<<< orphan*/  Suff_FindDeps (TYPE_1__*) ; 
 int /*<<< orphan*/  TARGET ; 
 int /*<<< orphan*/  Var_Set (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,scalar_t__) ; 
 char* strchr (char*,char) ; 

void
Make_ExpandUse(Lst targs)
{
    GNode  *gn;		/* a temporary pointer */
    Lst    examine; 	/* List of targets to examine */

    examine = Lst_Duplicate(targs, NULL);

    /*
     * Make an initial downward pass over the graph, marking nodes to be made
     * as we go down. We call Suff_FindDeps to find where a node is and
     * to get some children for it if it has none and also has no commands.
     * If the node is a leaf, we stick it on the toBeMade queue to
     * be looked at in a minute, otherwise we add its children to our queue
     * and go on about our business.
     */
    while (!Lst_IsEmpty (examine)) {
	gn = (GNode *)Lst_DeQueue(examine);
    
	if (gn->flags & REMAKE)
	    /* We've looked at this one already */
	    continue;
	gn->flags |= REMAKE;
	if (DEBUG(MAKE))
	    fprintf(debug_file, "Make_ExpandUse: examine %s%s\n",
		    gn->name, gn->cohort_num);

	if ((gn->type & OP_DOUBLEDEP) && !Lst_IsEmpty (gn->cohorts)) {
	    /* Append all the 'cohorts' to the list of things to examine */
	    Lst new;
	    new = Lst_Duplicate(gn->cohorts, NULL);
	    Lst_Concat(new, examine, LST_CONCLINK);
	    examine = new;
	}

	/*
	 * Apply any .USE rules before looking for implicit dependencies
	 * to make sure everything has commands that should...
	 * Make sure that the TARGET is set, so that we can make
	 * expansions.
	 */
	if (gn->type & OP_ARCHV) {
	    char *eoa, *eon;
	    eoa = strchr(gn->name, '(');
	    eon = strchr(gn->name, ')');
	    if (eoa == NULL || eon == NULL)
		continue;
	    *eoa = '\0';
	    *eon = '\0';
	    Var_Set(MEMBER, eoa + 1, gn, 0);
	    Var_Set(ARCHIVE, gn->name, gn, 0);
	    *eoa = '(';
	    *eon = ')';
	}

	(void)Dir_MTime(gn, 0);
	Var_Set(TARGET, gn->path ? gn->path : gn->name, gn, 0);
	Lst_ForEach(gn->children, MakeUnmark, gn);
	Lst_ForEach(gn->children, MakeHandleUse, gn);

	if ((gn->type & OP_MADE) == 0)
	    Suff_FindDeps(gn);
	else {
	    /* Pretend we made all this node's children */
	    Lst_ForEach(gn->children, MakeFindChild, gn);
	    if (gn->unmade != 0)
		    printf("Warning: %s%s still has %d unmade children\n",
			    gn->name, gn->cohort_num, gn->unmade);
	}

	if (gn->unmade != 0)
	    Lst_ForEach(gn->children, MakeAddChild, examine);
    }

    Lst_Destroy(examine, NULL);
}