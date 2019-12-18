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
struct TYPE_5__ {int type; int /*<<< orphan*/  unmade; int /*<<< orphan*/  children; } ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/ * Lst_Member (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Make_HandleUse (TYPE_1__*,TYPE_1__*) ; 
 int OP_MARK ; 
 int OP_USE ; 
 int OP_USEBEFORE ; 

__attribute__((used)) static int
MakeHandleUse(void *cgnp, void *pgnp)
{
    GNode	*cgn = (GNode *)cgnp;
    GNode	*pgn = (GNode *)pgnp;
    LstNode	ln; 	/* An element in the children list */
    int		unmarked;

    unmarked = ((cgn->type & OP_MARK) == 0);
    cgn->type |= OP_MARK;

    if ((cgn->type & (OP_USE|OP_USEBEFORE)) == 0)
	return (0);

    if (unmarked)
	Make_HandleUse(cgn, pgn);

    /*
     * This child node is now "made", so we decrement the count of
     * unmade children in the parent... We also remove the child
     * from the parent's list to accurately reflect the number of decent
     * children the parent has. This is used by Make_Run to decide
     * whether to queue the parent or examine its children...
     */
    if ((ln = Lst_Member(pgn->children, cgn)) != NULL) {
	Lst_Remove(pgn->children, ln);
	pgn->unmade--;
    }
    return (0);
}