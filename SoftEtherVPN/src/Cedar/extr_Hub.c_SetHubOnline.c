#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_16__ {scalar_t__ Type; int Offline; TYPE_2__* Cedar; int /*<<< orphan*/  lock_online; int /*<<< orphan*/  Name; int /*<<< orphan*/  SecureNATOption; int /*<<< orphan*/ * SecureNAT; scalar_t__ EnableSecureNAT; } ;
struct TYPE_15__ {int /*<<< orphan*/  LimitBroadcast; int /*<<< orphan*/  TapMacAddress; int /*<<< orphan*/  TapMode; int /*<<< orphan*/  Monitor; int /*<<< orphan*/  Local; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/ * Bridge; int /*<<< orphan*/  HubName; } ;
struct TYPE_14__ {TYPE_1__* Server; int /*<<< orphan*/  LocalBridgeList; } ;
struct TYPE_13__ {scalar_t__ ServerType; } ;
typedef  TYPE_3__ LOCALBRIDGE ;
typedef  TYPE_4__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * BrNewBridge (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  HLog (TYPE_4__*,char*) ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiHubOnlineProc (TYPE_4__*) ; 
 int /*<<< orphan*/ * SnNewSecureNAT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartAllLink (TYPE_4__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SetHubOnline(HUB *h)
{
	bool for_cluster = false;
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	if (h->Cedar->Server != NULL && h->Cedar->Server->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		if (h->Type == HUB_TYPE_FARM_DYNAMIC)
		{
			for_cluster = true;
		}
	}

	Lock(h->lock_online);
	{
		if (h->Offline == false)
		{
			Unlock(h->lock_online);
			return;
		}
		HLog(h, "LH_ONLINE");

		// Start all links
		StartAllLink(h);

		// Start the SecureNAT
		if (h->EnableSecureNAT)
		{
			if (h->SecureNAT == NULL)
			{
				if (for_cluster == false)
				{
					h->SecureNAT = SnNewSecureNAT(h, h->SecureNATOption);
				}
			}
		}

		// Start all of the local bridges that is associated with this HUB
		if (h->Type != HUB_TYPE_FARM_DYNAMIC)
		{
			LockList(h->Cedar->LocalBridgeList);
			{
				UINT i;
				for (i = 0;i < LIST_NUM(h->Cedar->LocalBridgeList);i++)
				{
					LOCALBRIDGE *br = LIST_DATA(h->Cedar->LocalBridgeList, i);

					if (StrCmpi(br->HubName, h->Name) == 0)
					{
						if (br->Bridge == NULL)
						{
							br->Bridge = BrNewBridge(h, br->DeviceName, NULL, br->Local, br->Monitor,
								br->TapMode, br->TapMacAddress, br->LimitBroadcast, br);
						}
					}
				}
			}
			UnlockList(h->Cedar->LocalBridgeList);
		}

		h->Offline = false;
	}
	Unlock(h->lock_online);

	if (h->Cedar->Server != NULL)
	{
		SiHubOnlineProc(h);
	}
}