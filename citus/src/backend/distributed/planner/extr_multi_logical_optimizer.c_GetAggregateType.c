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
typedef  size_t uint32 ;
typedef  char* Oid ;
typedef  size_t AggregateType ;

/* Variables and functions */
 size_t AGGREGATE_CUSTOM ; 
 scalar_t__ AGGREGATE_INVALID_FIRST ; 
 scalar_t__ AggregateEnabledCustom (char*) ; 
 char** AggregateNames ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_func_name (char*) ; 
 size_t lengthof (char**) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static AggregateType
GetAggregateType(Oid aggFunctionId)
{
	char *aggregateProcName = NULL;
	uint32 aggregateCount = 0;
	uint32 aggregateIndex = 0;
	bool found = false;

	/* look up the function name */
	aggregateProcName = get_func_name(aggFunctionId);
	if (aggregateProcName == NULL)
	{
		ereport(ERROR, (errmsg("citus cache lookup failed for function %u",
							   aggFunctionId)));
	}

	aggregateCount = lengthof(AggregateNames);

	Assert(AGGREGATE_INVALID_FIRST == 0);

	for (aggregateIndex = 1; aggregateIndex < aggregateCount; aggregateIndex++)
	{
		const char *aggregateName = AggregateNames[aggregateIndex];
		if (strncmp(aggregateName, aggregateProcName, NAMEDATALEN) == 0)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		if (AggregateEnabledCustom(aggFunctionId))
		{
			return AGGREGATE_CUSTOM;
		}

		ereport(ERROR, (errmsg("unsupported aggregate function %s", aggregateProcName)));
	}

	return aggregateIndex;
}