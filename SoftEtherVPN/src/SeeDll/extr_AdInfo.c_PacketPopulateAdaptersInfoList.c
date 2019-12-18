#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* Next; struct TYPE_5__* NetworkAddresses; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PADAPTER_INFO ;

/* Variables and functions */
 TYPE_1__* AdaptersInfoList ; 
 int /*<<< orphan*/  AdaptersInfoMutex ; 
 int /*<<< orphan*/  GlobalFreePtr (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ODS (char*) ; 
 int /*<<< orphan*/  PacketAddFakeNdisWanAdapter () ; 
 int /*<<< orphan*/  PacketGetAdapters () ; 
 int /*<<< orphan*/  PacketGetAdaptersDag () ; 
 int /*<<< orphan*/  PacketGetAdaptersIPH () ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p_dagc_open ; 

void PacketPopulateAdaptersInfoList()
{
	//this function should acquire the AdaptersInfoMutex, since it's NOT called with an ADAPTER_INFO as parameter
	PADAPTER_INFO TAdInfo;
	PVOID Mem1, Mem2;

	WaitForSingleObject(AdaptersInfoMutex, INFINITE);

	if(AdaptersInfoList)
	{
		// Free the old list
		TAdInfo = AdaptersInfoList;
		while(TAdInfo != NULL)
		{
			Mem1 = TAdInfo->NetworkAddresses;
			Mem2 = TAdInfo;
			
			TAdInfo = TAdInfo->Next;
			
			if (Mem1 != NULL)
				GlobalFreePtr(Mem1);
			GlobalFreePtr(Mem2);
		}
		
		AdaptersInfoList = NULL;
	}

	//
	// Fill the new list
	//
	if(!PacketGetAdapters())
	{
		// No info about adapters in the registry. 
		ODS("PacketPopulateAdaptersInfoList: registry scan for adapters failed!\n");
	}
#ifndef _WINNT4
	if(!PacketGetAdaptersIPH())
	{
		// IP Helper API not present. We are under WinNT 4 or TCP/IP is not installed
		ODS("PacketPopulateAdaptersInfoList: failed to get adapters from the IP Helper API!\n");
	}

	if (!PacketAddFakeNdisWanAdapter())
	{
		ODS("PacketPopulateAdaptersInfoList: adding fake NdisWan adapter failed.\n");
	}

#ifdef HAVE_DAG_API
	if(p_dagc_open == NULL)	
	{}	// dagc.dll not present on this system.
	else
	{
		if(!PacketGetAdaptersDag())
		{
			// No info about adapters in the registry. 
			ODS("PacketPopulateAdaptersInfoList: lookup of dag cards failed!\n");
		}
	}
#endif // HAVE_DAG_API

#endif // _WINNT4

	ReleaseMutex(AdaptersInfoMutex);
}