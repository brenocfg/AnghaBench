#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ varattno; int /*<<< orphan*/  varno; } ;
typedef  TYPE_1__ Var ;
struct TYPE_15__ {int /*<<< orphan*/  equivalentAttributes; } ;
struct TYPE_14__ {scalar_t__ varattno; int /*<<< orphan*/  relationId; int /*<<< orphan*/  rteIdentity; int /*<<< orphan*/  varno; } ;
struct TYPE_13__ {scalar_t__ rtekind; int /*<<< orphan*/  relid; } ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ AttributeEquivalenceClassMember ;
typedef  TYPE_4__ AttributeEquivalenceClass ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* DistPartitionKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRTEIdentity (TYPE_2__*) ; 
 int /*<<< orphan*/  IsDistributedTable (int /*<<< orphan*/ ) ; 
 scalar_t__ RTE_RELATION ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* palloc0 (int) ; 

__attribute__((used)) static void
AddRteRelationToAttributeEquivalenceClass(AttributeEquivalenceClass **
										  attrEquivalenceClass,
										  RangeTblEntry *rangeTableEntry,
										  Var *varToBeAdded)
{
	AttributeEquivalenceClassMember *attributeEqMember = NULL;
	Oid relationId = rangeTableEntry->relid;
	Var *relationPartitionKey = NULL;

	/* we don't consider local tables in the equality on columns */
	if (!IsDistributedTable(relationId))
	{
		return;
	}

	relationPartitionKey = DistPartitionKey(relationId);

	Assert(rangeTableEntry->rtekind == RTE_RELATION);

	/* we don't need reference tables in the equality on columns */
	if (relationPartitionKey == NULL)
	{
		return;
	}

	/* we're only interested in distribution columns */
	if (relationPartitionKey->varattno != varToBeAdded->varattno)
	{
		return;
	}

	attributeEqMember = palloc0(sizeof(AttributeEquivalenceClassMember));

	attributeEqMember->varattno = varToBeAdded->varattno;
	attributeEqMember->varno = varToBeAdded->varno;
	attributeEqMember->rteIdentity = GetRTEIdentity(rangeTableEntry);
	attributeEqMember->relationId = rangeTableEntry->relid;

	(*attrEquivalenceClass)->equivalentAttributes =
		lappend((*attrEquivalenceClass)->equivalentAttributes,
				attributeEqMember);
}