#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_5__* InformationBuffer; } ;
struct TYPE_8__ {scalar_t__ Oid; } ;
struct TYPE_10__ {TYPE_2__ SET_INFORMATION; TYPE_1__ QUERY_INFORMATION; } ;
struct TYPE_12__ {scalar_t__ RequestType; TYPE_3__ DATA; } ;
struct TYPE_11__ {int /*<<< orphan*/  NumPendingOidRequests; } ;
typedef  TYPE_4__ SL_ADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  TYPE_5__ NDIS_OID_REQUEST ;
typedef  scalar_t__ NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 scalar_t__ NdisRequestQueryInformation ; 
 scalar_t__ OID_GEN_VENDOR_DESCRIPTION ; 
 int /*<<< orphan*/  SlFree (TYPE_5__*) ; 

void SlNdisOidRequestCompleteProc(NDIS_HANDLE protocol_binding_context, NDIS_OID_REQUEST *oid_request, NDIS_STATUS status)
{
	SL_ADAPTER *a = (SL_ADAPTER *)protocol_binding_context;
	bool no_not_free = false;

	// Check the results
	if (oid_request->RequestType == NdisRequestQueryInformation)
	{
		if (oid_request->DATA.QUERY_INFORMATION.Oid == OID_GEN_VENDOR_DESCRIPTION)
		{
			no_not_free = true;
		}
	}

	// Release the memory
	if (no_not_free == false)
	{
		SlFree(oid_request->DATA.SET_INFORMATION.InformationBuffer);
	}

	SlFree(oid_request);

	// Counter subtraction
	InterlockedDecrement(&a->NumPendingOidRequests);
}