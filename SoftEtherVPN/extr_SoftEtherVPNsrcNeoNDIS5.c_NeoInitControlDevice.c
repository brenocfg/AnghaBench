#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE ;
struct TYPE_2__ {char* HardwarePrintableID; scalar_t__ HardwareID_Raw; scalar_t__ HardwareID; int /*<<< orphan*/  NdisControl; int /*<<< orphan*/ * NdisControlDevice; int /*<<< orphan*/ * DispatchTable; int /*<<< orphan*/  NdisWrapper; int /*<<< orphan*/  Opened; } ;
typedef  int /*<<< orphan*/  PDRIVER_DISPATCH ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;
typedef  int /*<<< orphan*/  DEVICE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetUnicode (int /*<<< orphan*/ *) ; 
 size_t IRP_MJ_CLOSE ; 
 size_t IRP_MJ_CREATE ; 
 size_t IRP_MJ_DEVICE_CONTROL ; 
 int IRP_MJ_MAXIMUM_FUNCTION ; 
 size_t IRP_MJ_READ ; 
 size_t IRP_MJ_WRITE ; 
 int MAX_SIZE ; 
 char* NDIS_NEO_DEVICE_NAME ; 
 char* NDIS_NEO_DEVICE_NAME_WIN32 ; 
 char* NDIS_NEO_HARDWARE_ID ; 
 int /*<<< orphan*/  NdisMRegisterDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoNdisDispatch ; 
 int /*<<< orphan*/  NeoZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NewUnicode (char*) ; 
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int strlen (scalar_t__) ; 

void NeoInitControlDevice()
{
	char name_kernel[MAX_SIZE];
	char name_win32[MAX_SIZE];
	UNICODE *unicode_kernel, *unicode_win32;
	DEVICE_OBJECT *control_device_object;
	NDIS_HANDLE ndis_control_handle;

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

	// Generate the device name
	sprintf(name_kernel, NDIS_NEO_DEVICE_NAME, ctx->HardwareID);
	unicode_kernel = NewUnicode(name_kernel);
	sprintf(name_win32, NDIS_NEO_DEVICE_NAME_WIN32, ctx->HardwareID);
	unicode_win32 = NewUnicode(name_win32);

	// Register the Device
	NdisMRegisterDevice(ctx->NdisWrapper, GetUnicode(unicode_kernel),
		GetUnicode(unicode_win32), ctx->DispatchTable,
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