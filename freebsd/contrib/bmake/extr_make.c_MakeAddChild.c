#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int type; char* name; int /*<<< orphan*/  cohort_num; } ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_EnQueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MAKE ; 
 int OP_USE ; 
 int OP_USEBEFORE ; 
 int REMAKE ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
MakeAddChild(void *gnp, void *lp)
{
    GNode          *gn = (GNode *)gnp;
    Lst            l = (Lst) lp;

    if ((gn->flags & REMAKE) == 0 && !(gn->type & (OP_USE|OP_USEBEFORE))) {
	if (DEBUG(MAKE))
	    fprintf(debug_file, "MakeAddChild: need to examine %s%s\n",
		gn->name, gn->cohort_num);
	(void)Lst_EnQueue(l, gn);
    }
    return (0);
}