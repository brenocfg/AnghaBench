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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE_ALL_NODES ; 
 int /*<<< orphan*/ * DetachPartitionCommandList () ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  REMOVE_ALL_CLUSTERED_TABLES_COMMAND ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
MetadataDropCommands(void)
{
	List *dropSnapshotCommandList = NIL;
	List *detachPartitionCommandList = DetachPartitionCommandList();

	dropSnapshotCommandList = list_concat(dropSnapshotCommandList,
										  detachPartitionCommandList);

	dropSnapshotCommandList = lappend(dropSnapshotCommandList,
									  REMOVE_ALL_CLUSTERED_TABLES_COMMAND);

	dropSnapshotCommandList = lappend(dropSnapshotCommandList, DELETE_ALL_NODES);

	return dropSnapshotCommandList;
}