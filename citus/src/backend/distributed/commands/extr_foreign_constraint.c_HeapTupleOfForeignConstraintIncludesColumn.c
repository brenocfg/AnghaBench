#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/  DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2OID ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 char* get_attname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
HeapTupleOfForeignConstraintIncludesColumn(HeapTuple heapTuple, Oid relationId,
										   int pgConstraintKey, char *columnName)
{
	Datum columnsDatum = 0;
	Datum *columnArray = NULL;
	int columnCount = 0;
	int attrIdx = 0;
	bool isNull = false;

	columnsDatum = SysCacheGetAttr(CONSTROID, heapTuple, pgConstraintKey, &isNull);
	deconstruct_array(DatumGetArrayTypeP(columnsDatum), INT2OID, 2, true,
					  's', &columnArray, NULL, &columnCount);

	for (attrIdx = 0; attrIdx < columnCount; ++attrIdx)
	{
		AttrNumber attrNo = DatumGetInt16(columnArray[attrIdx]);

		char *colName = get_attname(relationId, attrNo, false);
		if (strncmp(colName, columnName, NAMEDATALEN) == 0)
		{
			return true;
		}
	}

	return false;
}