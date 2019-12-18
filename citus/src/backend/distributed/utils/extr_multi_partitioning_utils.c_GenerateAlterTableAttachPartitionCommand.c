#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 char* PartitionBound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PartitionTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* generate_qualified_relation_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_partition_parent (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 

char *
GenerateAlterTableAttachPartitionCommand(Oid partitionTableId)
{
	StringInfo createPartitionCommand = makeStringInfo();
	char *partitionBoundCString = NULL;

	Oid parentId = InvalidOid;
	char *tableQualifiedName = NULL;
	char *parentTableQualifiedName = NULL;

	if (!PartitionTable(partitionTableId))
	{
		char *relationName = get_rel_name(partitionTableId);

		ereport(ERROR, (errmsg("\"%s\" is not a partition", relationName)));
	}

	parentId = get_partition_parent(partitionTableId);
	tableQualifiedName = generate_qualified_relation_name(partitionTableId);
	parentTableQualifiedName = generate_qualified_relation_name(parentId);

	partitionBoundCString = PartitionBound(partitionTableId);

	appendStringInfo(createPartitionCommand, "ALTER TABLE %s ATTACH PARTITION %s %s;",
					 parentTableQualifiedName, tableQualifiedName,
					 partitionBoundCString);

	return createPartitionCommand->data;
}