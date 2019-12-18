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
struct TYPE_3__ {scalar_t__ rtekind; char relkind; } ;
typedef  TYPE_1__ RangeTblEntry ;

/* Variables and functions */
 char RELKIND_FOREIGN_TABLE ; 
 char RELKIND_MATVIEW ; 
 char RELKIND_PARTITIONED_TABLE ; 
 char RELKIND_RELATION ; 
 scalar_t__ RTE_RELATION ; 

__attribute__((used)) static bool
CitusQueryableRangeTableRelation(RangeTblEntry *rangeTableEntry)
{
	char relationKind = '\0';

	if (rangeTableEntry->rtekind != RTE_RELATION)
	{
		/* we're only interested in relations */
		return false;
	}

	relationKind = rangeTableEntry->relkind;
	if (relationKind == RELKIND_RELATION || relationKind == RELKIND_PARTITIONED_TABLE ||
		relationKind == RELKIND_FOREIGN_TABLE || relationKind == RELKIND_MATVIEW)
	{
		/*
		 * RELKIND_VIEW are automatically replaced with a subquery in
		 * the query tree, so we ignore them here.
		 *
		 * RELKIND_MATVIEW is equivalent of a local table in postgres.
		 */
		return true;
	}

	return false;
}