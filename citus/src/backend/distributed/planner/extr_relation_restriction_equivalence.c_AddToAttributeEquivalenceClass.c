#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ varattno; size_t varno; } ;
typedef  TYPE_1__ Var ;
struct TYPE_13__ {TYPE_2__** simple_rte_array; } ;
struct TYPE_12__ {scalar_t__ rtekind; } ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  AttributeEquivalenceClass ;

/* Variables and functions */
 int /*<<< orphan*/  AddRteRelationToAttributeEquivalenceClass (int /*<<< orphan*/ **,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRteSubqueryToAttributeEquivalenceClass (int /*<<< orphan*/ **,TYPE_2__*,TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ InvalidAttrNumber ; 
 scalar_t__ RTE_RELATION ; 
 scalar_t__ RTE_SUBQUERY ; 

__attribute__((used)) static void
AddToAttributeEquivalenceClass(AttributeEquivalenceClass **attributeEquivalanceClass,
							   PlannerInfo *root, Var *varToBeAdded)
{
	RangeTblEntry *rangeTableEntry = NULL;

	/* punt if it's a whole-row var rather than a plain column reference */
	if (varToBeAdded->varattno == InvalidAttrNumber)
	{
		return;
	}

	/* we also don't want to process ctid, tableoid etc */
	if (varToBeAdded->varattno < InvalidAttrNumber)
	{
		return;
	}

	rangeTableEntry = root->simple_rte_array[varToBeAdded->varno];
	if (rangeTableEntry->rtekind == RTE_RELATION)
	{
		AddRteRelationToAttributeEquivalenceClass(attributeEquivalanceClass,
												  rangeTableEntry,
												  varToBeAdded);
	}
	else if (rangeTableEntry->rtekind == RTE_SUBQUERY)
	{
		AddRteSubqueryToAttributeEquivalenceClass(attributeEquivalanceClass,
												  rangeTableEntry, root,
												  varToBeAdded);
	}
}