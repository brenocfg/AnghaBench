#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Next; struct TYPE_4__* NetworkAddresses; int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_1__* PADAPTER_INFO ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_1__* AdaptersInfoList ; 
 int /*<<< orphan*/  AdaptersInfoMutex ; 
 scalar_t__ AddAdapter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAKE_NDISWAN_ADAPTER_NAME ; 
 int /*<<< orphan*/  GlobalFreePtr (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  PacketAddFakeNdisWanAdapter () ; 
 int /*<<< orphan*/  PacketGetAdaptersDag () ; 
 int /*<<< orphan*/  PacketGetAdaptersIPH () ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p_dagc_open ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN PacketUpdateAdInfo(PCHAR AdapterName)
{
	//this function should acquire the AdaptersInfoMutex, since it's NOT called with an ADAPTER_INFO as parameter
	PADAPTER_INFO TAdInfo, PrevAdInfo;
	
	WaitForSingleObject(AdaptersInfoMutex, INFINITE);
	
	PrevAdInfo = TAdInfo = AdaptersInfoList;

	//
	// If an entry for this adapter is present in the list, we destroy it
	//
	while(TAdInfo != NULL)
	{
		if(strcmp(TAdInfo->Name, AdapterName) == 0)
		{
			if (strcmp(AdapterName, FAKE_NDISWAN_ADAPTER_NAME) == 0)
			{
				ReleaseMutex(AdaptersInfoMutex);
				return TRUE;
			}

			if(TAdInfo == AdaptersInfoList)
			{
				AdaptersInfoList = TAdInfo->Next;
			}
			else
			{
				PrevAdInfo->Next = TAdInfo->Next;
			}

			if (TAdInfo->NetworkAddresses != NULL)
				GlobalFreePtr(TAdInfo->NetworkAddresses);
			GlobalFreePtr(TAdInfo);

			break;
		}

		PrevAdInfo = TAdInfo;

		TAdInfo = TAdInfo->Next;
	}

	ReleaseMutex(AdaptersInfoMutex);

	//
	// Now obtain the information about this adapter
	//
	if(AddAdapter(AdapterName, 0) == TRUE)
		return TRUE;
#ifndef _WINNT4
	// 
	// Not a tradiditonal adapter, but possibly a Wan or DAG interface 
	// Gather all the available adapters from IPH API and dagc API
	//
	PacketGetAdaptersIPH();
	PacketAddFakeNdisWanAdapter();
#ifdef HAVE_DAG_API
	if(p_dagc_open == NULL)	
		return TRUE;	// dagc.dll not present on this system.
	else
	PacketGetAdaptersDag();
#endif // HAVE_DAG_API

#endif // _WINNT4

	// Adapter not found
	return TRUE;
}