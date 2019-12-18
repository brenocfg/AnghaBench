#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_6__ {int natts; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  CopyCoercionData ;

/* Variables and functions */
 int /*<<< orphan*/  ConversionPathForTypes (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__* TypeArrayFromTupleDescriptor (TYPE_1__*) ; 
 scalar_t__ TypeForColumnName (scalar_t__,TYPE_1__*,char*) ; 
 char* lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * palloc0 (int) ; 

__attribute__((used)) static CopyCoercionData *
ColumnCoercionPaths(TupleDesc destTupleDescriptor, TupleDesc inputTupleDescriptor,
					Oid destRelId, List *columnNameList,
					Oid *finalColumnTypeArray)
{
	int columnIndex = 0;
	int columnCount = inputTupleDescriptor->natts;
	CopyCoercionData *coercePaths = palloc0(columnCount * sizeof(CopyCoercionData));
	Oid *inputTupleTypes = TypeArrayFromTupleDescriptor(inputTupleDescriptor);
	ListCell *currentColumnName = list_head(columnNameList);

	for (columnIndex = 0; columnIndex < columnCount; columnIndex++)
	{
		Oid destTupleType = InvalidOid;
		Oid inputTupleType = inputTupleTypes[columnIndex];
		char *columnName = lfirst(currentColumnName);

		if (inputTupleType == InvalidOid)
		{
			/* this was a dropped column and will not be in the incoming tuples */
			continue;
		}

		destTupleType = TypeForColumnName(destRelId, destTupleDescriptor, columnName);

		finalColumnTypeArray[columnIndex] = destTupleType;

		ConversionPathForTypes(inputTupleType, destTupleType,
							   &coercePaths[columnIndex]);

		currentColumnName = lnext(currentColumnName);

		if (currentColumnName == NULL)
		{
			/* the rest of inputTupleDescriptor are dropped columns, return early! */
			break;
		}
	}

	return coercePaths;
}