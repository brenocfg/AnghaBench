#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_8__ {int /*<<< orphan*/  NumBoundAdapters; int /*<<< orphan*/  AdapterList; } ;
struct TYPE_7__ {int Halt; int IsClosePending; int NumPendingOidRequests; int NumPendingSendPackets; int /*<<< orphan*/ * UnbindContext; int /*<<< orphan*/  Lock; int /*<<< orphan*/ * AdapterHandle; TYPE_1__* Device; } ;
struct TYPE_6__ {int Halting; } ;
typedef  TYPE_2__ SL_ADAPTER ;
typedef  scalar_t__ NDIS_STATUS ;
typedef  int /*<<< orphan*/ * NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 scalar_t__ NDIS_STATUS_PENDING ; 
 scalar_t__ NDIS_STATUS_SUCCESS ; 
 scalar_t__ NdisCloseAdapterEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SlDelete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SlLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlLockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlNdisCloseAdapterCompleteExProc (TYPE_2__*) ; 
 int /*<<< orphan*/  SlUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlUnlockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* sl ; 

NDIS_STATUS SlNdisUnbindAdapterExProc(NDIS_HANDLE unbind_context, NDIS_HANDLE protocol_binding_context)
{
	NDIS_STATUS ret;
	SL_ADAPTER *a = (SL_ADAPTER *)protocol_binding_context;
	UINT j;
	NDIS_HANDLE adapter_handle = NULL;

	if (a->Halt)
	{
		//SL_WHERE;
	}

	adapter_handle = a->AdapterHandle;
	a->Halt = true;
	if (a->Device != NULL)
	{
		a->Device->Halting = true;
	}
	a->AdapterHandle = NULL;

	SlLock(a->Lock);
	{
	}
	SlUnlock(a->Lock);

	a->UnbindContext = unbind_context;
	a->IsClosePending = true;

	// Delete the adapter from the adapter list
	SlLockList(sl->AdapterList);
	{
		SlDelete(sl->AdapterList, a);
	}
	SlUnlockList(sl->AdapterList);

	for (j = 0;j < 32;j++)
	{
		// Wait until the number of OID requests of being processed by this adapter becomes zero
		while (true)
		{
			UINT num;

			num = a->NumPendingOidRequests;

			if (num == 0)
			{
				break;
			}
			else
			{
				j = 0;
			}

			//SlSleep(50);
		}

		// Wait until the number of packets this adapter is transmitting becomes zero
		while (true)
		{
			UINT num;

			num = a->NumPendingSendPackets;

			if (num == 0)
			{
				break;
			}
			else
			{
				j = 0;
			}

			//SlSleep(50);
		}

	}

	ret = NdisCloseAdapterEx(adapter_handle);

	if (ret != NDIS_STATUS_PENDING)
	{
		a->IsClosePending = false;
		SlNdisCloseAdapterCompleteExProc(a);

		ret = NDIS_STATUS_SUCCESS;

		InterlockedDecrement(&sl->NumBoundAdapters);
	}

	return ret;
}