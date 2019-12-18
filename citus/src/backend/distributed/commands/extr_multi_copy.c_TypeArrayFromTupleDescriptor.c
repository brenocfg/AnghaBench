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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  atttypid; scalar_t__ attisdropped; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * palloc0 (int) ; 

__attribute__((used)) static Oid *
TypeArrayFromTupleDescriptor(TupleDesc tupleDescriptor)
{
	int columnCount = tupleDescriptor->natts;
	Oid *typeArray = palloc0(columnCount * sizeof(Oid));
	int columnIndex = 0;

	for (columnIndex = 0; columnIndex < columnCount; columnIndex++)
	{
		Form_pg_attribute attr = TupleDescAttr(tupleDescriptor, columnIndex);
		if (attr->attisdropped)
		{
			typeArray[columnIndex] = InvalidOid;
		}
		else
		{
			typeArray[columnIndex] = attr->atttypid;
		}
	}

	return typeArray;
}