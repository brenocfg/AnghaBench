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
typedef  int /*<<< orphan*/  RenameStmt ;
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateRenameProcStmt (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * CreateRenameTypeStmt (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  ERROR ; 
#define  OCLASS_PROC 129 
#define  OCLASS_TYPE 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int getObjectClass (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static RenameStmt *
CreateRenameStatement(const ObjectAddress *address, char *newName)
{
	switch (getObjectClass(address))
	{
		case OCLASS_PROC:
		{
			return CreateRenameProcStmt(address, newName);
		}

		case OCLASS_TYPE:
		{
			return CreateRenameTypeStmt(address, newName);
		}

		default:
		{
			ereport(ERROR, (errmsg("unsupported object to construct a rename statement"),
							errdetail("unable to generate a parsetree for the rename")));
		}
	}
}