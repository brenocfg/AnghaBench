#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int Local; int Monitor; int TapMode; int LimitBroadcast; int /*<<< orphan*/  TapMacAddress; int /*<<< orphan*/ * ParentLocalBridge; TYPE_1__* Policy; int /*<<< orphan*/  Name; TYPE_2__* Hub; int /*<<< orphan*/  Cedar; } ;
struct TYPE_13__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_12__ {int MonitorPort; int NoBroadcastLimiter; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ POLICY ;
typedef  int /*<<< orphan*/  LOCALBRIDGE ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_3__ BRIDGE ;

/* Variables and functions */
 int /*<<< orphan*/  BrBridgeThread ; 
 TYPE_1__* ClonePolicy (TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GenMacAddress (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetDefaultPolicy () ; 
 int IsZero (char*,int) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_3__* ZeroMalloc (int) ; 

BRIDGE *BrNewBridge(HUB *h, char *name, POLICY *p, bool local, bool monitor, bool tapmode, char *tapaddr, bool limit_broadcast, LOCALBRIDGE *parent_local_bridge)
{
	BRIDGE *b;
	POLICY *policy;
	THREAD *t;
	// Validate arguments
	if (h == NULL || name == NULL || parent_local_bridge == NULL)
	{
		return NULL;
	}

	if (p == NULL)
	{
		policy = ClonePolicy(GetDefaultPolicy());
	}
	else
	{
		policy = ClonePolicy(p);
	}

	b = ZeroMalloc(sizeof(BRIDGE));
	b->Cedar = h->Cedar;
	b->Hub = h;
	StrCpy(b->Name, sizeof(b->Name), name);
	b->Policy = policy;
	b->Local = local;
	b->Monitor = monitor;
	b->TapMode = tapmode;
	b->LimitBroadcast = limit_broadcast;
	b->ParentLocalBridge = parent_local_bridge;

	if (b->TapMode)
	{
		if (tapaddr != NULL && IsZero(tapaddr, 6) == false)
		{
			Copy(b->TapMacAddress, tapaddr, 6);
		}
		else
		{
			GenMacAddress(b->TapMacAddress);
		}
	}

	if (monitor)
	{
		// Enabling monitoring mode
		policy->MonitorPort = true;
	}

	if (b->LimitBroadcast == false)
	{
		// Disable broadcast limiter
		policy->NoBroadcastLimiter = true;
	}

	// Start thread
	t = NewThread(BrBridgeThread, b);
	WaitThreadInit(t);
	ReleaseThread(t);

	return b;
}