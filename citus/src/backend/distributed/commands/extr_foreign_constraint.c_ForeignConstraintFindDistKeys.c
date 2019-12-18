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
struct TYPE_4__ {scalar_t__ varattno; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_constraint_confkey ; 
 int /*<<< orphan*/  Anum_pg_constraint_conkey ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/  DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2OID ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
ForeignConstraintFindDistKeys(HeapTuple pgConstraintTuple,
							  Var *referencingDistColumn,
							  Var *referencedDistColumn,
							  int *referencingAttrIndex,
							  int *referencedAttrIndex)
{
	Datum referencingColumnsDatum = 0;
	Datum *referencingColumnArray = NULL;
	int referencingColumnCount = 0;
	Datum referencedColumnsDatum = 0;
	Datum *referencedColumnArray = NULL;
	int referencedColumnCount = 0;
	bool isNull = false;
	int attrIdx = 0;

	*referencedAttrIndex = -1;
	*referencedAttrIndex = -1;

	/*
	 * Column attributes are not available in Form_pg_constraint, therefore we need
	 * to find them in the system catalog. After finding them, we iterate over column
	 * attributes together because partition column must be at the same place in both
	 * referencing and referenced side of the foreign key constraint.
	 */
	referencingColumnsDatum = SysCacheGetAttr(CONSTROID, pgConstraintTuple,
											  Anum_pg_constraint_conkey, &isNull);
	referencedColumnsDatum = SysCacheGetAttr(CONSTROID, pgConstraintTuple,
											 Anum_pg_constraint_confkey, &isNull);

	deconstruct_array(DatumGetArrayTypeP(referencingColumnsDatum), INT2OID, 2, true,
					  's', &referencingColumnArray, NULL, &referencingColumnCount);
	deconstruct_array(DatumGetArrayTypeP(referencedColumnsDatum), INT2OID, 2, true,
					  's', &referencedColumnArray, NULL, &referencedColumnCount);

	Assert(referencingColumnCount == referencedColumnCount);

	for (attrIdx = 0; attrIdx < referencingColumnCount; ++attrIdx)
	{
		AttrNumber referencingAttrNo = DatumGetInt16(referencingColumnArray[attrIdx]);
		AttrNumber referencedAttrNo = DatumGetInt16(referencedColumnArray[attrIdx]);

		if (referencedDistColumn != NULL &&
			referencedDistColumn->varattno == referencedAttrNo)
		{
			*referencedAttrIndex = attrIdx;
		}

		if (referencingDistColumn != NULL &&
			referencingDistColumn->varattno == referencingAttrNo)
		{
			*referencingAttrIndex = attrIdx;
		}
	}
}