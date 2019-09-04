#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_18__ {int /*<<< orphan*/  NumBoundAdapters; int /*<<< orphan*/  AdapterList; } ;
struct TYPE_17__ {int IsOpenPending; int Ready; int /*<<< orphan*/ * AdapterHandle; TYPE_3__* Device; int /*<<< orphan*/  FriendlyName; int /*<<< orphan*/  AdapterId; scalar_t__ BindingContext; } ;
struct TYPE_16__ {TYPE_4__* Adapter; int /*<<< orphan*/  FileList; } ;
struct TYPE_14__ {scalar_t__ Buffer; } ;
struct TYPE_15__ {TYPE_1__ String; } ;
typedef  TYPE_2__ SL_UNICODE ;
typedef  TYPE_3__ SL_DEVICE ;
typedef  TYPE_4__ SL_ADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  scalar_t__ NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 scalar_t__ NG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisCompleteBindAdapterEx (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OID_GEN_VENDOR_DESCRIPTION ; 
 scalar_t__ OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SL_ADAPTER_DEVICE_NAME ; 
 int /*<<< orphan*/  SL_ADAPTER_DEVICE_NAME_SYMBOLIC ; 
 int /*<<< orphan*/  SlAdd (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SlCopy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SlFreeAdapter (TYPE_4__*) ; 
 int /*<<< orphan*/  SlFreeUnicode (TYPE_2__*) ; 
 int /*<<< orphan*/  SlLockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* SlNewDeviceUnicode (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SlNewList () ; 
 TYPE_2__* SlNewUnicode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlSendOidRequest (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SlUnlockList (int /*<<< orphan*/ ) ; 
 TYPE_5__* sl ; 

void SlNdisOpenAdapterCompleteExProc(NDIS_HANDLE protocol_binding_context, NDIS_STATUS status)
{
	SL_ADAPTER *a = (SL_ADAPTER *)protocol_binding_context;
	bool is_pending = a->IsOpenPending;
	NDIS_HANDLE binding_context = a->BindingContext;

	if (OK(status))
	{
		// Create an adapter device
		SL_UNICODE *device_name = SlNewUnicode(SL_ADAPTER_DEVICE_NAME);
		SL_UNICODE *symbolic_name = SlNewUnicode(SL_ADAPTER_DEVICE_NAME_SYMBOLIC);
		SL_DEVICE *dev;

		// Create a device name
		SlCopy(device_name->String.Buffer + 8, a->AdapterId, sizeof(wchar_t) * 46);
		SlCopy(symbolic_name->String.Buffer + 19, a->AdapterId, sizeof(wchar_t) * 46);

		dev = SlNewDeviceUnicode(device_name, symbolic_name);

		if (dev == NULL)
		{
			// Device creation failed
			SlFreeUnicode(device_name);
			SlFreeUnicode(symbolic_name);
		}
		else
		{
			// Create a file list
			dev->FileList = SlNewList();
		}
		if (dev != NULL)
		{
			// Get the display name
			SlSendOidRequest(a, false, OID_GEN_VENDOR_DESCRIPTION, a->FriendlyName,
				sizeof(a->FriendlyName) - 1);

			dev->Adapter = a;
			a->Device = dev;

			// Add this adapter to the adapter list
			SlLockList(sl->AdapterList);
			{
				SlAdd(sl->AdapterList, a);
			}
			SlUnlockList(sl->AdapterList);
		}
	}
	else
	{
		// Discard the adapter handle
		a->AdapterHandle = NULL;

		// Release the SL_ADAPTER
		SlFreeAdapter(a);

		a = NULL;
	}

	if (is_pending)
	{
		NdisCompleteBindAdapterEx(binding_context, status);
	}

	if (a != NULL)
	{
		a->Ready = true;
	}

	if (is_pending)
	{
		if (NG(status))
		{
			InterlockedDecrement(&sl->NumBoundAdapters);
		}
	}
}