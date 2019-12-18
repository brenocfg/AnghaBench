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
struct TYPE_3__ {int /*<<< orphan*/  object; int /*<<< orphan*/  renameType; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  const* FunctionToObjectAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ObjectWithArgs ; 
 int /*<<< orphan*/  castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const ObjectAddress *
RenameFunctionStmtObjectAddress(RenameStmt *stmt, bool missing_ok)
{
	return FunctionToObjectAddress(stmt->renameType,
								   castNode(ObjectWithArgs, stmt->object), missing_ok);
}