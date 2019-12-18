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
typedef  int /*<<< orphan*/  ShardPlacementAccessType ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CheckConflictingRelationAccesses (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PartitionTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PartitionedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordPlacementAccessToCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RecordRelationAccessBase(Oid relationId, ShardPlacementAccessType accessType)
{
	/*
	 * We call this only for reference tables, and we don't support partitioned
	 * reference tables.
	 */
	Assert(!PartitionedTable(relationId) && !PartitionTable(relationId));

	/* make sure that this is not a conflicting access */
	CheckConflictingRelationAccesses(relationId, accessType);

	/* always record the relation that is being considered */
	RecordPlacementAccessToCache(relationId, accessType);
}