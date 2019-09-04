#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  macstr ;
struct TYPE_22__ {int /*<<< orphan*/  Ref; } ;
struct TYPE_21__ {int Halt; int IsRawIpMode; int Active; scalar_t__ NextWaitTimeForRetry; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  CurrentMacAddress; int /*<<< orphan*/  Lock; TYPE_7__* HaltTube; scalar_t__ PublicIP; TYPE_13__* v; } ;
struct TYPE_19__ {int /*<<< orphan*/  ServerAddress; } ;
struct TYPE_20__ {int IsIpRawMode; int /*<<< orphan*/  DnsServerIP; TYPE_4__ CurrentDhcpOptionList; TYPE_3__* Ipc; int /*<<< orphan*/  DeviceName; TYPE_2__* Sock2; int /*<<< orphan*/ * Sock1; } ;
struct TYPE_18__ {int /*<<< orphan*/  BroadcastAddress; int /*<<< orphan*/  DefaultGateway; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  ClientIPAddress; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_17__ {TYPE_7__* RecvTube; } ;
struct TYPE_16__ {scalar_t__ DisableIpRawModeSecureNAT; scalar_t__ DisableKernelModeSecureNAT; } ;
struct TYPE_15__ {int UseNat; TYPE_1__* HubOption; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_5__ NATIVE_STACK ;
typedef  TYPE_6__ NATIVE_NAT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  FreeNativeStack (TYPE_5__*) ; 
 int /*<<< orphan*/  FreeWaitUntilHostIPAddressChanged (void*) ; 
 scalar_t__ IPToUINT (int /*<<< orphan*/ *) ; 
 void* InitWaitUntilHostIPAddressChanged () ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLog (TYPE_13__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NnClearQueue (TYPE_6__*) ; 
 TYPE_5__* NnGetNextInterface (TYPE_6__*) ; 
 int /*<<< orphan*/  NnMainLoop (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseTube (TYPE_7__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WaitUntilHostIPAddressChanged (void*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ ,int) ; 

void NativeNatThread(THREAD *thread, void *param)
{
	NATIVE_NAT *t = (NATIVE_NAT *)param;
	void *wait_handle = InitWaitUntilHostIPAddressChanged();
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	while (t->Halt == false)
	{
		NATIVE_STACK *a;

		while (t->v->UseNat == false || t->v->HubOption == NULL || (t->v->HubOption->DisableKernelModeSecureNAT && t->v->HubOption->DisableIpRawModeSecureNAT))
		{
			if (t->Halt)
			{
				break;
			}

			// If the NAT is disabled, wait until it becomes enabled
			Wait(t->HaltEvent, 1234);	
		}

		if (t->Halt)
		{
			break;
		}

		// Get a next good native NAT stack
		Debug("NnGetNextInterface Start.\n");

		NnClearQueue(t);

		a = NnGetNextInterface(t);

		if (a != NULL)
		{
			char macstr[64];
			// Acquisition success
			Debug("NnGetNextInterface Ok: %s\n", a->DeviceName);

			t->IsRawIpMode = a->IsIpRawMode;

			Lock(t->Lock);
			{
				if (a->Sock1 != NULL)
				{
					t->HaltTube = a->Sock2->RecvTube;

					if (t->HaltTube != NULL)
					{
						AddRef(t->HaltTube->Ref);
					}
				}
			}
			Unlock(t->Lock);

			NnClearQueue(t);

			t->PublicIP = IPToUINT(&a->Ipc->ClientIPAddress);
			t->Active = true;


			Debug("NnMainLoop Start.\n");
			MacToStr(macstr, sizeof(macstr), a->Ipc->MacAddress);
			NLog(t->v, "LH_KERNEL_MODE_START", a->DeviceName,
				&a->Ipc->ClientIPAddress, &a->Ipc->SubnetMask, &a->Ipc->DefaultGateway, &a->Ipc->BroadcastAddress,
				macstr, &a->CurrentDhcpOptionList.ServerAddress, &a->DnsServerIP);
			NnMainLoop(t, a);
			Debug("NnMainLoop End.\n");

			t->IsRawIpMode = false;

			t->Active = false;
			t->PublicIP = 0;


			NnClearQueue(t);

			// Close the stack
			Lock(t->Lock);
			{
				if (t->HaltTube != NULL)
				{
					ReleaseTube(t->HaltTube);
					t->HaltTube = NULL;
				}
			}
			Unlock(t->Lock);
			FreeNativeStack(a);

			Zero(t->CurrentMacAddress, 6);
		}
		else
		{
			Debug("NnGetNextInterface Failed.\n");
		}

		// Wait for a certain period of time
		if (t->NextWaitTimeForRetry != 0)
		{
			WaitUntilHostIPAddressChanged(wait_handle, t->HaltEvent, t->NextWaitTimeForRetry, 1000);
		}
	}

	FreeWaitUntilHostIPAddressChanged(wait_handle);
}