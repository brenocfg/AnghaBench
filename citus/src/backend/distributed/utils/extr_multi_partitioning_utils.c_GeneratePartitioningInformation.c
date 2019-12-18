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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PartitionedTable (int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_get_partkeydef ; 

char *
GeneratePartitioningInformation(Oid parentTableId)
{
	char *partitionBoundCString = "";
	Datum partitionBoundDatum = 0;

	if (!PartitionedTable(parentTableId))
	{
		char *relationName = get_rel_name(parentTableId);

		ereport(ERROR, (errmsg("\"%s\" is not a parent table", relationName)));
	}

	partitionBoundDatum = DirectFunctionCall1(pg_get_partkeydef,
											  ObjectIdGetDatum(parentTableId));

	partitionBoundCString = TextDatumGetCString(partitionBoundDatum);

	return partitionBoundCString;
}