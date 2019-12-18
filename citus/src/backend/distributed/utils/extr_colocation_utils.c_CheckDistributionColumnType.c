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
struct TYPE_3__ {scalar_t__ vartype; } ;
typedef  TYPE_1__ Var ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 TYPE_1__* DistPartitionKey (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 char* get_rel_name (scalar_t__) ; 

void
CheckDistributionColumnType(Oid sourceRelationId, Oid targetRelationId)
{
	Var *sourceDistributionColumn = NULL;
	Var *targetDistributionColumn = NULL;
	Oid sourceDistributionColumnType = InvalidOid;
	Oid targetDistributionColumnType = InvalidOid;

	/* reference tables have NULL distribution column */
	sourceDistributionColumn = DistPartitionKey(sourceRelationId);
	if (sourceDistributionColumn == NULL)
	{
		sourceDistributionColumnType = InvalidOid;
	}
	else
	{
		sourceDistributionColumnType = sourceDistributionColumn->vartype;
	}

	/* reference tables have NULL distribution column */
	targetDistributionColumn = DistPartitionKey(targetRelationId);
	if (targetDistributionColumn == NULL)
	{
		targetDistributionColumnType = InvalidOid;
	}
	else
	{
		targetDistributionColumnType = targetDistributionColumn->vartype;
	}

	if (sourceDistributionColumnType != targetDistributionColumnType)
	{
		char *sourceRelationName = get_rel_name(sourceRelationId);
		char *targetRelationName = get_rel_name(targetRelationId);

		ereport(ERROR, (errmsg("cannot colocate tables %s and %s",
							   sourceRelationName, targetRelationName),
						errdetail("Distribution column types don't match for "
								  "%s and %s.", sourceRelationName,
								  targetRelationName)));
	}
}