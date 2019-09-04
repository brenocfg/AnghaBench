#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_14__ {scalar_t__ Type; int BeingOffline; int Offline; TYPE_2__* Cedar; int /*<<< orphan*/  lock_online; int /*<<< orphan*/  Name; int /*<<< orphan*/ * SecureNAT; scalar_t__ Halt; } ;
struct TYPE_13__ {int /*<<< orphan*/ * Bridge; int /*<<< orphan*/  HubName; } ;
struct TYPE_12__ {TYPE_1__* Server; int /*<<< orphan*/  LocalBridgeList; } ;
struct TYPE_11__ {scalar_t__ ServerType; } ;
typedef  TYPE_3__ LOCALBRIDGE ;
typedef  TYPE_4__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  BrFreeBridge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HLog (TYPE_4__*,char*) ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiHubOfflineProc (TYPE_4__*) ; 
 int /*<<< orphan*/  SnFreeSecureNAT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopAllLink (TYPE_4__*) ; 
 int /*<<< orphan*/  StopAllSession (TYPE_4__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SetHubOffline(HUB *h)
{
	UINT i;
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

	h->BeingOffline = true;

	Lock(h->lock_online);
	{
		if (h->Offline || h->Halt)
		{
			Unlock(h->lock_online);
			h->BeingOffline = false;
			return;
		}

		HLog(h, "LH_OFFLINE");

		// Stop all links
		StopAllLink(h);

		// Stop the SecureNAT
		SnFreeSecureNAT(h->SecureNAT);
		h->SecureNAT = NULL;

		// Stop all the local bridges that is associated with this HUB
		LockList(h->Cedar->LocalBridgeList);
		{
			for (i = 0;i < LIST_NUM(h->Cedar->LocalBridgeList);i++)
			{
				LOCALBRIDGE *br = LIST_DATA(h->Cedar->LocalBridgeList, i);

				if (StrCmpi(br->HubName, h->Name) == 0)
				{
					BrFreeBridge(br->Bridge);
					br->Bridge = NULL;
				}
			}
		}
		UnlockList(h->Cedar->LocalBridgeList);

		// Offline
		h->Offline = true;

		// Disconnect all sessions
		StopAllSession(h);
	}
	Unlock(h->lock_online);

	h->BeingOffline = false;

	if (h->Cedar->Server != NULL)
	{
		SiHubOfflineProc(h);
	}
}