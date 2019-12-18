#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  HubList; int /*<<< orphan*/  LocalBridgeList; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Bridge; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ LOCALBRIDGE ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  BrFreeBridge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool DeleteLocalBridge(CEDAR *c, char *hubname, char *devicename)
{
	bool ret = false;
	// Validate arguments
	if (c == NULL || hubname == NULL || devicename == NULL)
	{
		return false;
	}

	LockList(c->HubList);
	{
		LockList(c->LocalBridgeList);
		{
			UINT i;

			for (i = 0;i < LIST_NUM(c->LocalBridgeList);i++)
			{
				LOCALBRIDGE *br = LIST_DATA(c->LocalBridgeList, i);

				if (StrCmpi(br->HubName, hubname) == 0)
				{
					if (StrCmpi(br->DeviceName, devicename) == 0)
					{
						if (br->Bridge != NULL)
						{
							BrFreeBridge(br->Bridge);
							br->Bridge = NULL;
						}

						Delete(c->LocalBridgeList, br);
						Free(br);

						ret = true;
						break;
					}
				}
			}
		}
		UnlockList(c->LocalBridgeList);
	}
	UnlockList(c->HubList);

	return ret;
}