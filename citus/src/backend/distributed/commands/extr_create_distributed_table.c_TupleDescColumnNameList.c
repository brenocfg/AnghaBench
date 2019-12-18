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
struct TYPE_7__ {scalar_t__ attgenerated; scalar_t__ attisdropped; int /*<<< orphan*/  attname; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 scalar_t__ ATTRIBUTE_GENERATED_STORED ; 
 int /*<<< orphan*/ * NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static List *
TupleDescColumnNameList(TupleDesc tupleDescriptor)
{
	List *columnNameList = NIL;
	int columnIndex = 0;

	for (columnIndex = 0; columnIndex < tupleDescriptor->natts; columnIndex++)
	{
		Form_pg_attribute currentColumn = TupleDescAttr(tupleDescriptor, columnIndex);
		char *columnName = NameStr(currentColumn->attname);

		if (currentColumn->attisdropped
#if PG_VERSION_NUM >= 120000
			|| currentColumn->attgenerated == ATTRIBUTE_GENERATED_STORED
#endif
			)
		{
			continue;
		}

		columnNameList = lappend(columnNameList, columnName);
	}

	return columnNameList;
}