#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  objectId; } ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTypeStmtByObjectAddress (TYPE_1__ const*) ; 
 char const* DeparseTreeNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 char const* GetFunctionDDLCommand (int /*<<< orphan*/ ,int) ; 
#define  OCLASS_PROC 129 
#define  OCLASS_TYPE 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int getObjectClass (TYPE_1__ const*) ; 

__attribute__((used)) static const char *
CreateStmtByObjectAddress(const ObjectAddress *address)
{
	switch (getObjectClass(address))
	{
		case OCLASS_PROC:
		{
			return GetFunctionDDLCommand(address->objectId, false);
		}

		case OCLASS_TYPE:
		{
			return DeparseTreeNode(CreateTypeStmtByObjectAddress(address));
		}

		default:
		{
			ereport(ERROR, (errmsg(
								"unsupported object to construct a create statement")));
		}
	}
}