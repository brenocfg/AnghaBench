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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ DYN_VALUE ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dyn_value_list ; 

UINT64 GetDynValue(char *name)
{
	UINT64 ret = 0;
	// Validate arguments
	if (name == NULL)
	{
		return 0;
	}

	if (g_dyn_value_list == NULL)
	{
		return 0;
	}

	LockList(g_dyn_value_list);
	{
		UINT i;

		for (i = 0; i < LIST_NUM(g_dyn_value_list);i++)
		{
			DYN_VALUE *vv = LIST_DATA(g_dyn_value_list, i);

			if (StrCmpi(vv->Name, name) == 0)
			{
				ret = vv->Value;
				break;
			}
		}
	}
	UnlockList(g_dyn_value_list);

	return ret;
}