#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; int unmade_cohorts; int /*<<< orphan*/  cohort_num; struct TYPE_5__* centurion; int /*<<< orphan*/  cohorts; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int OP_DOUBLEDEP ; 
 int OP_INVISIBLE ; 
 int /*<<< orphan*/  OP_NOP (int) ; 
 int OP_OPMASK ; 
 int /*<<< orphan*/  PARSE_FATAL ; 
 int /*<<< orphan*/  ParseMark (TYPE_1__*) ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARG_NOHASH ; 
 TYPE_1__* Targ_FindNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ doing_depend ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int
ParseDoOp(void *gnp, void *opp)
{
    GNode          *gn = (GNode *)gnp;
    int             op = *(int *)opp;
    /*
     * If the dependency mask of the operator and the node don't match and
     * the node has actually had an operator applied to it before, and
     * the operator actually has some dependency information in it, complain.
     */
    if (((op & OP_OPMASK) != (gn->type & OP_OPMASK)) &&
	!OP_NOP(gn->type) && !OP_NOP(op))
    {
	Parse_Error(PARSE_FATAL, "Inconsistent operator for %s", gn->name);
	return (1);
    }

    if ((op == OP_DOUBLEDEP) && ((gn->type & OP_OPMASK) == OP_DOUBLEDEP)) {
	/*
	 * If the node was the object of a :: operator, we need to create a
	 * new instance of it for the children and commands on this dependency
	 * line. The new instance is placed on the 'cohorts' list of the
	 * initial one (note the initial one is not on its own cohorts list)
	 * and the new instance is linked to all parents of the initial
	 * instance.
	 */
	GNode	*cohort;

	/*
	 * Propagate copied bits to the initial node.  They'll be propagated
	 * back to the rest of the cohorts later.
	 */
	gn->type |= op & ~OP_OPMASK;

	cohort = Targ_FindNode(gn->name, TARG_NOHASH);
	if (doing_depend)
	    ParseMark(cohort);
	/*
	 * Make the cohort invisible as well to avoid duplicating it into
	 * other variables. True, parents of this target won't tend to do
	 * anything with their local variables, but better safe than
	 * sorry. (I think this is pointless now, since the relevant list
	 * traversals will no longer see this node anyway. -mycroft)
	 */
	cohort->type = op | OP_INVISIBLE;
	(void)Lst_AtEnd(gn->cohorts, cohort);
	cohort->centurion = gn;
	gn->unmade_cohorts += 1;
	snprintf(cohort->cohort_num, sizeof cohort->cohort_num, "#%d",
		gn->unmade_cohorts);
    } else {
	/*
	 * We don't want to nuke any previous flags (whatever they were) so we
	 * just OR the new operator into the old
	 */
	gn->type |= op;
    }

    return (0);
}