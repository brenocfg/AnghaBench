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
struct TYPE_7__ {int flags; int type; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  ALLSRC ; 
 int DONE_ALLSRC ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MakeAddAllSrc ; 
 int /*<<< orphan*/  MakeUnmark ; 
 int /*<<< orphan*/  OODATE ; 
 int OP_JOIN ; 
 int /*<<< orphan*/  TARGET ; 
 int /*<<< orphan*/  Var_Exists (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Var_Set (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* Var_Value (int /*<<< orphan*/ ,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 

void
Make_DoAllVar(GNode *gn)
{
    if (gn->flags & DONE_ALLSRC)
	return;
    
    Lst_ForEach(gn->children, MakeUnmark, gn);
    Lst_ForEach(gn->children, MakeAddAllSrc, gn);

    if (!Var_Exists (OODATE, gn)) {
	Var_Set(OODATE, "", gn, 0);
    }
    if (!Var_Exists (ALLSRC, gn)) {
	Var_Set(ALLSRC, "", gn, 0);
    }

    if (gn->type & OP_JOIN) {
	char *p1;
	Var_Set(TARGET, Var_Value(ALLSRC, gn, &p1), gn, 0);
	free(p1);
    }
    gn->flags |= DONE_ALLSRC;
}