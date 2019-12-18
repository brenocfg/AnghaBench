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
struct TYPE_3__ {int type; int /*<<< orphan*/  name; int /*<<< orphan*/  cohorts; } ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LST_CONCNEW ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int OP_DOUBLEDEP ; 
 int /*<<< orphan*/  Punt (char*) ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Append (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mainNode ; 

Lst
Parse_MainName(void)
{
    Lst           mainList;	/* result list */

    mainList = Lst_Init(FALSE);

    if (mainNode == NULL) {
	Punt("no target to make.");
    	/*NOTREACHED*/
    } else if (mainNode->type & OP_DOUBLEDEP) {
	(void)Lst_AtEnd(mainList, mainNode);
	Lst_Concat(mainList, mainNode->cohorts, LST_CONCNEW);
    }
    else
	(void)Lst_AtEnd(mainList, mainNode);
    Var_Append(".TARGETS", mainNode->name, VAR_GLOBAL);
    return (mainList);
}