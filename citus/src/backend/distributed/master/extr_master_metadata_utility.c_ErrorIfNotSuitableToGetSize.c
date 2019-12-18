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

/* Variables and functions */
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TABLE_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsDistributedTable (int /*<<< orphan*/ ) ; 
 scalar_t__ PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SingleReplicatedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 char* quote_literal_cstr (char*) ; 

__attribute__((used)) static void
ErrorIfNotSuitableToGetSize(Oid relationId)
{
	if (!IsDistributedTable(relationId))
	{
		char *relationName = get_rel_name(relationId);
		char *escapedQueryString = quote_literal_cstr(relationName);
		ereport(ERROR, (errcode(ERRCODE_INVALID_TABLE_DEFINITION),
						errmsg("cannot calculate the size because relation %s is not "
							   "distributed", escapedQueryString)));
	}

	if (PartitionMethod(relationId) == DISTRIBUTE_BY_HASH &&
		!SingleReplicatedTable(relationId))
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot calculate the size because replication factor "
							   "is greater than 1")));
	}
}