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
 int /*<<< orphan*/  EnsureTableOwner (int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 

void
CheckTableSchemaNameForDrop(Oid relationId, char **schemaName, char **tableName)
{
	char *tempTableName = get_rel_name(relationId);

	if (tempTableName != NULL)
	{
		/* ensure proper values are used if the table exists */
		Oid schemaId = get_rel_namespace(relationId);
		(*schemaName) = get_namespace_name(schemaId);
		(*tableName) = tempTableName;

		EnsureTableOwner(relationId);
	}
}