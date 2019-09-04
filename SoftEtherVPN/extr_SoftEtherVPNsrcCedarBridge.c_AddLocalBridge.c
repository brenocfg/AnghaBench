#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  OsType; } ;
struct TYPE_14__ {int /*<<< orphan*/  LocalBridgeList; int /*<<< orphan*/  HubList; } ;
struct TYPE_13__ {char* Name; scalar_t__ Type; int Offline; int /*<<< orphan*/  lock_online; int /*<<< orphan*/  ref; } ;
struct TYPE_12__ {char* DeviceName; char* HubName; int TapMode; int Local; int LimitBroadcast; int Monitor; int /*<<< orphan*/  TapMacAddress; int /*<<< orphan*/ * Bridge; } ;
typedef  TYPE_1__ LOCALBRIDGE ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BrNewBridge (TYPE_2__*,char*,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GenMacAddress (int /*<<< orphan*/ ) ; 
 TYPE_7__* GetOsInfo () ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 scalar_t__ IsInList (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int IsZero (char*,int) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int OS_IS_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_2__*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void AddLocalBridge(CEDAR *c, char *hubname, char *devicename, bool local, bool monitor, bool tapmode, char *tapaddr, bool limit_broadcast)
{
	UINT i;
	HUB *h = NULL;
	LOCALBRIDGE *br = NULL;
	// Validate arguments
	if (c == NULL || hubname == NULL || devicename == NULL)
	{
		return;
	}

	if (OS_IS_UNIX(GetOsInfo()->OsType) == false)
	{
		tapmode = false;
	}

	LockList(c->HubList);
	{
		LockList(c->LocalBridgeList);
		{
			bool exists = false;

			// Ensure that the same configuration local-bridge doesn't exist already 
			for (i = 0;i < LIST_NUM(c->LocalBridgeList);i++)
			{
				LOCALBRIDGE *br = LIST_DATA(c->LocalBridgeList, i);
				if (StrCmpi(br->DeviceName, devicename) == 0)
				{
					if (StrCmpi(br->HubName, hubname) == 0)
					{
						if (br->TapMode == tapmode)
						{
							exists = true;
						}
					}
				}
			}

			if (exists == false)
			{
				// Add configuration
				br = ZeroMalloc(sizeof(LOCALBRIDGE));
				StrCpy(br->HubName, sizeof(br->HubName), hubname);
				StrCpy(br->DeviceName, sizeof(br->DeviceName), devicename);
				br->Bridge = NULL;
				br->Local = local;
				br->TapMode = tapmode;
				br->LimitBroadcast = limit_broadcast;
				br->Monitor = monitor;
				if (br->TapMode)
				{
					if (tapaddr != NULL && IsZero(tapaddr, 6) == false)
					{
						Copy(br->TapMacAddress, tapaddr, 6);
					}
					else
					{
						GenMacAddress(br->TapMacAddress);
					}
				}

				Add(c->LocalBridgeList, br);

				// Find the hub
				for (i = 0;i < LIST_NUM(c->HubList);i++)
				{
					HUB *hub = LIST_DATA(c->HubList, i);
					if (StrCmpi(hub->Name, br->HubName) == 0)
					{
						h = hub;
						AddRef(h->ref);
						break;
					}
				}
			}
		}
		UnlockList(c->LocalBridgeList);
	}
	UnlockList(c->HubList);

	// Start the local-bridge immediately
	if (h != NULL && br != NULL && h->Type != HUB_TYPE_FARM_DYNAMIC)
	{
		Lock(h->lock_online);
		{
			if (h->Offline == false)
			{
				LockList(c->LocalBridgeList);
				{
					if (IsInList(c->LocalBridgeList, br))
					{
						if (br->Bridge == NULL)
						{
							br->Bridge = BrNewBridge(h, br->DeviceName, NULL, br->Local, br->Monitor, br->TapMode, br->TapMacAddress, br->LimitBroadcast, br);
						}
					}
				}
				UnlockList(c->LocalBridgeList);
			}
		}
		Unlock(h->lock_online);
	}

	ReleaseHub(h);
}