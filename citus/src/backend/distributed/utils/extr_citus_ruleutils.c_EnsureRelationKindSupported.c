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
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsChildTable (int /*<<< orphan*/ ) ; 
 scalar_t__ IsParentTable (int /*<<< orphan*/ ) ; 
 char RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RegularTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 

void
EnsureRelationKindSupported(Oid relationId)
{
	char relationKind = get_rel_relkind(relationId);
	bool supportedRelationKind = false;

	supportedRelationKind = RegularTable(relationId) ||
							relationKind == RELKIND_FOREIGN_TABLE;

	/*
	 * Citus doesn't support bare inherited tables (i.e., not a partition or
	 * partitioned table)
	 */
	supportedRelationKind = supportedRelationKind && !(IsChildTable(relationId) ||
													   IsParentTable(relationId));

	if (!supportedRelationKind)
	{
		char *relationName = get_rel_name(relationId);

		ereport(ERROR, (errcode(ERRCODE_WRONG_OBJECT_TYPE),
						errmsg("%s is not a regular, foreign or partitioned table",
							   relationName)));
	}
}