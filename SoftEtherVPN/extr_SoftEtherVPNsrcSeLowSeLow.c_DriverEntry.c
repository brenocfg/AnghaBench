#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_22__ {int IsBasicDevice; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* DriverUnload ) (TYPE_4__*) ;TYPE_3__* MajorFunction; } ;
struct TYPE_18__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Revision; int /*<<< orphan*/  Type; } ;
struct TYPE_20__ {int MajorNdisVersion; int MinorNdisVersion; TYPE_9__* BasicDevice; int /*<<< orphan*/ * ProtocolHandle; int /*<<< orphan*/  AdapterList; TYPE_4__* DriverObject; int /*<<< orphan*/  SendNetBufferListsCompleteHandler; int /*<<< orphan*/  ReceiveNetBufferListsHandler; int /*<<< orphan*/  StatusHandlerEx; int /*<<< orphan*/  OidRequestCompleteHandler; int /*<<< orphan*/  UninstallHandler; int /*<<< orphan*/  NetPnPEventHandler; int /*<<< orphan*/  CloseAdapterCompleteHandlerEx; int /*<<< orphan*/  OpenAdapterCompleteHandlerEx; int /*<<< orphan*/  UnbindAdapterHandlerEx; int /*<<< orphan*/  BindAdapterHandlerEx; int /*<<< orphan*/  Name; TYPE_1__ Header; } ;
struct TYPE_19__ {int /*<<< orphan*/  String; } ;
typedef  TYPE_2__ SL_UNICODE ;
typedef  int /*<<< orphan*/  SL_CTX ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  TYPE_3__ NDIS_PROTOCOL_DRIVER_CHARACTERISTICS ;
typedef  int /*<<< orphan*/ * NDIS_HANDLE ;
typedef  TYPE_4__ DRIVER_OBJECT ;
typedef  int /*<<< orphan*/  DEVICE_OBJECT ;

/* Variables and functions */
 size_t IRP_MJ_CLOSE ; 
 size_t IRP_MJ_CREATE ; 
 size_t IRP_MJ_DEVICE_CONTROL ; 
 size_t IRP_MJ_READ ; 
 size_t IRP_MJ_WRITE ; 
 int /*<<< orphan*/  NDIS_OBJECT_TYPE_PROTOCOL_DRIVER_CHARACTERISTICS ; 
 int /*<<< orphan*/  NDIS_PROTOCOL_DRIVER_CHARACTERISTICS_REVISION_2 ; 
 int /*<<< orphan*/  NDIS_SIZEOF_PROTOCOL_DRIVER_CHARACTERISTICS_REVISION_2 ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 scalar_t__ NG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisRegisterProtocolDriver (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SL_BASIC_DEVICE_NAME ; 
 int /*<<< orphan*/  SL_BASIC_DEVICE_NAME_SYMBOLIC ; 
 int /*<<< orphan*/  SL_PROTOCOL_NAME ; 
 TYPE_3__ SlDeviceCloseProc ; 
 TYPE_3__ SlDeviceIoControlProc ; 
 TYPE_3__ SlDeviceOpenProc ; 
 TYPE_3__ SlDeviceReadProc ; 
 TYPE_3__ SlDeviceWriteProc ; 
 int /*<<< orphan*/  SlFreeUnicode (TYPE_2__*) ; 
 int /*<<< orphan*/  SlNdisBindAdapterExProc ; 
 int /*<<< orphan*/  SlNdisCloseAdapterCompleteExProc ; 
 int /*<<< orphan*/  SlNdisNetPnPEventProc ; 
 int /*<<< orphan*/  SlNdisOidRequestCompleteProc ; 
 int /*<<< orphan*/  SlNdisOpenAdapterCompleteExProc ; 
 int /*<<< orphan*/  SlNdisReceiveNetBufferListsProc ; 
 int /*<<< orphan*/  SlNdisSendNetBufferListsCompleteProc ; 
 int /*<<< orphan*/  SlNdisStatusExProc ; 
 int /*<<< orphan*/  SlNdisUnbindAdapterExProc ; 
 int /*<<< orphan*/  SlNdisUninstallProc ; 
 TYPE_9__* SlNewDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlNewList () ; 
 TYPE_2__* SlNewUnicode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlUnloadProc (TYPE_4__*) ; 
 int /*<<< orphan*/  SlZero (TYPE_3__*,int) ; 
 TYPE_3__* sl ; 

NDIS_STATUS DriverEntry(DRIVER_OBJECT *driver_object, UNICODE_STRING *registry_path)
{
	NDIS_PROTOCOL_DRIVER_CHARACTERISTICS t;
	NDIS_STATUS ret = NDIS_STATUS_FAILURE;
	SL_UNICODE *protocol_name = NULL;
	NDIS_HANDLE protocol_handle = NULL;
	SL_CTX *sl_ctx = NULL;
	DEVICE_OBJECT *device_object = NULL;

	SlZero(sl, sizeof(SL_CTX));

	// Register the NDIS protocol
	protocol_name = SlNewUnicode(SL_PROTOCOL_NAME);
	if (protocol_name == NULL)
	{
		goto LABEL_CLEANUP;
	}

	SlZero(&t, sizeof(t));
	t.Header.Type = NDIS_OBJECT_TYPE_PROTOCOL_DRIVER_CHARACTERISTICS;
	t.Header.Revision = NDIS_PROTOCOL_DRIVER_CHARACTERISTICS_REVISION_2;
	t.Header.Size = NDIS_SIZEOF_PROTOCOL_DRIVER_CHARACTERISTICS_REVISION_2;
	t.MajorNdisVersion = 6;
	t.MinorNdisVersion = 20;
	t.Name = protocol_name->String;

	t.BindAdapterHandlerEx = SlNdisBindAdapterExProc;
	t.UnbindAdapterHandlerEx = SlNdisUnbindAdapterExProc;
	t.OpenAdapterCompleteHandlerEx = SlNdisOpenAdapterCompleteExProc;
	t.CloseAdapterCompleteHandlerEx = SlNdisCloseAdapterCompleteExProc;
	t.NetPnPEventHandler = SlNdisNetPnPEventProc;
	t.UninstallHandler = SlNdisUninstallProc;
	t.OidRequestCompleteHandler = SlNdisOidRequestCompleteProc;
	t.StatusHandlerEx = SlNdisStatusExProc;
	t.ReceiveNetBufferListsHandler = SlNdisReceiveNetBufferListsProc;
	t.SendNetBufferListsCompleteHandler = SlNdisSendNetBufferListsCompleteProc;

	// Create an adapters list
	sl->DriverObject = driver_object;
	sl->AdapterList = SlNewList();

	ret = NdisRegisterProtocolDriver(NULL, &t, &protocol_handle);

	if (NG(ret))
	{
		protocol_handle = NULL;
		goto LABEL_CLEANUP;
	}

	SlZero(driver_object->MajorFunction, sizeof(driver_object->MajorFunction));
	driver_object->MajorFunction[IRP_MJ_CREATE] = SlDeviceOpenProc;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = SlDeviceCloseProc;
	driver_object->MajorFunction[IRP_MJ_READ] = SlDeviceReadProc;
	driver_object->MajorFunction[IRP_MJ_WRITE] = SlDeviceWriteProc;
	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = SlDeviceIoControlProc;
	driver_object->DriverUnload = SlUnloadProc;

	// Initialize the SL context
	sl->ProtocolHandle = protocol_handle;

	// Create a basic device
	sl->BasicDevice = SlNewDevice(SL_BASIC_DEVICE_NAME, SL_BASIC_DEVICE_NAME_SYMBOLIC);
	if (sl->BasicDevice == NULL)
	{
		ret = NDIS_STATUS_FAILURE;
		goto LABEL_CLEANUP;
	}
	sl->BasicDevice->IsBasicDevice = true;

LABEL_CLEANUP:

	SlFreeUnicode(protocol_name);

	if (NG(ret))
	{
		SlUnloadProc(driver_object);
	}

	return ret;
}