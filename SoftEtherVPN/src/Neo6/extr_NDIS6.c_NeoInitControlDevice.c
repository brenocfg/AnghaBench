#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  UNICODE ;
struct TYPE_9__ {char* HardwarePrintableID; scalar_t__ HardwareID_Raw; scalar_t__ HardwareID; int /*<<< orphan*/  NdisControl; int /*<<< orphan*/ * NdisControlDevice; TYPE_2__* DispatchTable; void* Paused; void* Opened; } ;
struct TYPE_7__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Revision; int /*<<< orphan*/  Type; } ;
struct TYPE_8__ {struct TYPE_8__* MajorFunctions; void* SymbolicName; void* DeviceName; TYPE_1__ Header; } ;
typedef  int /*<<< orphan*/  PDRIVER_DISPATCH ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;
typedef  TYPE_2__ NDIS_DEVICE_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  DEVICE_OBJECT ;

/* Variables and functions */
 void* FALSE ; 
 void* GetUnicode (int /*<<< orphan*/ *) ; 
 size_t IRP_MJ_CLOSE ; 
 size_t IRP_MJ_CREATE ; 
 size_t IRP_MJ_DEVICE_CONTROL ; 
 int IRP_MJ_MAXIMUM_FUNCTION ; 
 size_t IRP_MJ_READ ; 
 size_t IRP_MJ_WRITE ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NDIS_DEVICE_OBJECT_ATTRIBUTES_REVISION_1 ; 
 char* NDIS_NEO_DEVICE_NAME ; 
 char* NDIS_NEO_DEVICE_NAME_WIN32 ; 
 char* NDIS_NEO_HARDWARE_ID ; 
 int /*<<< orphan*/  NDIS_OBJECT_TYPE_DEVICE_OBJECT_ATTRIBUTES ; 
 int /*<<< orphan*/  NDIS_SIZEOF_DEVICE_OBJECT_ATTRIBUTES_REVISION_1 ; 
 int /*<<< orphan*/  NdisRegisterDeviceEx (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_2__ NeoNdisDispatch ; 
 int /*<<< orphan*/  NeoZero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * NewUnicode (char*) ; 
 TYPE_3__* ctx ; 
 int /*<<< orphan*/  ndis_miniport_driver_handle ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int strlen (scalar_t__) ; 

void NeoInitControlDevice()
{
	char name_kernel[MAX_SIZE];
	char name_win32[MAX_SIZE];
	UNICODE *unicode_kernel, *unicode_win32;
	DEVICE_OBJECT *control_device_object;
	NDIS_HANDLE ndis_control_handle;
	NDIS_DEVICE_OBJECT_ATTRIBUTES t;

	if (ctx == NULL)
	{
		return;
	}

	// Initialize the dispatch table
	NeoZero(ctx->DispatchTable, sizeof(PDRIVER_DISPATCH) * IRP_MJ_MAXIMUM_FUNCTION);

	// Register the handler
	ctx->DispatchTable[IRP_MJ_CREATE] =
		ctx->DispatchTable[IRP_MJ_CLOSE] =
		ctx->DispatchTable[IRP_MJ_READ] =
		ctx->DispatchTable[IRP_MJ_WRITE] =
		ctx->DispatchTable[IRP_MJ_DEVICE_CONTROL] = NeoNdisDispatch;
	ctx->Opened = FALSE;
	ctx->Paused = FALSE;

	// Generate the device name
	sprintf(name_kernel, NDIS_NEO_DEVICE_NAME, ctx->HardwareID);
	unicode_kernel = NewUnicode(name_kernel);
	sprintf(name_win32, NDIS_NEO_DEVICE_NAME_WIN32, ctx->HardwareID);
	unicode_win32 = NewUnicode(name_win32);

	// Register the device
	NeoZero(&t, sizeof(t));
	t.Header.Type = NDIS_OBJECT_TYPE_DEVICE_OBJECT_ATTRIBUTES;
	t.Header.Revision = NDIS_DEVICE_OBJECT_ATTRIBUTES_REVISION_1;
	t.Header.Size = NDIS_SIZEOF_DEVICE_OBJECT_ATTRIBUTES_REVISION_1;
	t.DeviceName = GetUnicode(unicode_kernel);
	t.SymbolicName = GetUnicode(unicode_win32);
	t.MajorFunctions = ctx->DispatchTable;

	NdisRegisterDeviceEx(ndis_miniport_driver_handle, &t,
		&control_device_object,
		&ndis_control_handle);

	ctx->NdisControlDevice = control_device_object;
	ctx->NdisControl = ndis_control_handle;

	// Initialize the display name
	if (strlen(ctx->HardwareID) > 11)
	{
		sprintf(ctx->HardwarePrintableID, NDIS_NEO_HARDWARE_ID, ctx->HardwareID_Raw + 11);
	}
	else
	{
		sprintf(ctx->HardwarePrintableID, NDIS_NEO_HARDWARE_ID, ctx->HardwareID_Raw);
	}
}