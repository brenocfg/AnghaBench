#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int cohort_num; int made; int type; scalar_t__ unmade_cohorts; scalar_t__ unmade; scalar_t__ cohorts; scalar_t__ order_pred; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 scalar_t__ DEFERRED ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_ForEach (scalar_t__,int (*) (void*,void*),void*) ; 
 int /*<<< orphan*/  Lst_InsertBefore (int /*<<< orphan*/ ,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  MAKE ; 
 int MakeCheckOrder (void*,void*) ; 
 int OP_WAIT ; 
 scalar_t__ REQUESTED ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int /*<<< orphan*/  toBeMade ; 

__attribute__((used)) static int
MakeBuildChild(void *v_cn, void *toBeMade_next)
{
    GNode *cn = v_cn;

    if (DEBUG(MAKE))
	fprintf(debug_file, "MakeBuildChild: inspect %s%s, made %d, type %x\n",
	    cn->name, cn->cohort_num, cn->made, cn->type);
    if (cn->made > DEFERRED)
	return 0;

    /* If this node is on the RHS of a .ORDER, check LHSs. */
    if (cn->order_pred && Lst_ForEach(cn->order_pred, MakeCheckOrder, 0)) {
	/* Can't build this (or anything else in this child list) yet */
	cn->made = DEFERRED;
	return 0;			/* but keep looking */
    }

    if (DEBUG(MAKE))
	fprintf(debug_file, "MakeBuildChild: schedule %s%s\n",
		cn->name, cn->cohort_num);

    cn->made = REQUESTED;
    if (toBeMade_next == NULL)
	Lst_AtEnd(toBeMade, cn);
    else
	Lst_InsertBefore(toBeMade, toBeMade_next, cn);

    if (cn->unmade_cohorts != 0)
	Lst_ForEach(cn->cohorts, MakeBuildChild, toBeMade_next);

    /*
     * If this node is a .WAIT node with unmade chlidren
     * then don't add the next sibling.
     */
    return cn->type & OP_WAIT && cn->unmade > 0;
}