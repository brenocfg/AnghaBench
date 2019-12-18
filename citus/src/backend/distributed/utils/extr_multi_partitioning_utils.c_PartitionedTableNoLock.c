#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* rd_rel; } ;
struct TYPE_5__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  heap_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* try_relation_open_nolock (int /*<<< orphan*/ ) ; 

bool
PartitionedTableNoLock(Oid relationId)
{
	Relation rel = try_relation_open_nolock(relationId);
	bool partitionedTable = false;

	/* don't error out for tables that are dropped */
	if (rel == NULL)
	{
		return false;
	}

	if (rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
	{
		partitionedTable = true;
	}

	/* keep the lock */
	heap_close(rel, NoLock);

	return partitionedTable;
}