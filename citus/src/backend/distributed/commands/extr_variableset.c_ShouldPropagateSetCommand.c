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
struct TYPE_3__ {int kind; int /*<<< orphan*/  name; int /*<<< orphan*/  is_local; } ;
typedef  TYPE_1__ VariableSetStmt ;

/* Variables and functions */
 int IsSettingSafeToPropagate (int /*<<< orphan*/ ) ; 
 scalar_t__ PROPSETCMD_LOCAL ; 
 scalar_t__ PropagateSetCommands ; 
#define  VAR_RESET 133 
#define  VAR_RESET_ALL 132 
#define  VAR_SET_CURRENT 131 
#define  VAR_SET_DEFAULT 130 
#define  VAR_SET_MULTI 129 
#define  VAR_SET_VALUE 128 

bool
ShouldPropagateSetCommand(VariableSetStmt *setStmt)
{
	if (PropagateSetCommands != PROPSETCMD_LOCAL)
	{
		/* SET propagation is disabled */
		return false;
	}

	switch (setStmt->kind)
	{
		case VAR_SET_VALUE:
		case VAR_SET_CURRENT:
		case VAR_SET_DEFAULT:
		{
			/* SET LOCAL on a safe setting */
			return setStmt->is_local && IsSettingSafeToPropagate(setStmt->name);
		}

		case VAR_RESET:
		{
			/* may need to reset prior SET LOCAL */
			return IsSettingSafeToPropagate(setStmt->name);
		}

		case VAR_RESET_ALL:
		{
			/* always propagate RESET ALL since it might affect prior SET LOCALs */
			return true;
		}

		case VAR_SET_MULTI:
		default:
		{
			/* SET (LOCAL) TRANSACTION should be handled locally */
			return false;
		}
	}
}