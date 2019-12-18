#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  plan_params; struct TYPE_7__* parent_root; } ;
struct TYPE_6__ {int /*<<< orphan*/  plan_params; TYPE_2__* root; } ;
typedef  TYPE_1__ RootPlanParams ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  CopyPlanParamList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* palloc0 (int) ; 

__attribute__((used)) static List *
OuterPlanParamsList(PlannerInfo *root)
{
	List *planParamsList = NIL;
	PlannerInfo *outerNodeRoot = NULL;

	for (outerNodeRoot = root->parent_root; outerNodeRoot != NULL;
		 outerNodeRoot = outerNodeRoot->parent_root)
	{
		RootPlanParams *rootPlanParams = palloc0(sizeof(RootPlanParams));
		rootPlanParams->root = outerNodeRoot;

		/*
		 * TODO: In SearchPlannerParamList() we are only interested in Var plan
		 * params, consider copying just them here.
		 */
		rootPlanParams->plan_params = CopyPlanParamList(outerNodeRoot->plan_params);

		planParamsList = lappend(planParamsList, rootPlanParams);
	}

	return planParamsList;
}