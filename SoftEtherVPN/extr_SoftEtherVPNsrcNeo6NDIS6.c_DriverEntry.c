#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Revision; int /*<<< orphan*/  Type; } ;
struct TYPE_6__ {int /*<<< orphan*/  CancelOidRequestHandler; int /*<<< orphan*/  ShutdownHandlerEx; int /*<<< orphan*/  DevicePnPEventNotifyHandler; int /*<<< orphan*/  CancelSendHandler; int /*<<< orphan*/  ReturnNetBufferListsHandler; int /*<<< orphan*/  RestartHandler; int /*<<< orphan*/  PauseHandler; int /*<<< orphan*/  SetOptionsHandler; int /*<<< orphan*/  SendNetBufferListsHandler; int /*<<< orphan*/  UnloadHandler; int /*<<< orphan*/  CheckForHangHandlerEx; int /*<<< orphan*/  ResetHandlerEx; int /*<<< orphan*/  OidRequestHandler; int /*<<< orphan*/  HaltHandlerEx; int /*<<< orphan*/  InitializeHandlerEx; int /*<<< orphan*/  MinorNdisVersion; int /*<<< orphan*/  MajorNdisVersion; TYPE_1__ Header; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  TYPE_2__ NDIS_MINIPORT_DRIVER_CHARACTERISTICS ;
typedef  int /*<<< orphan*/  DRIVER_OBJECT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NDIS_MINIPORT_DRIVER_CHARACTERISTICS_REVISION_2 ; 
 int /*<<< orphan*/  NDIS_OBJECT_TYPE_MINIPORT_DRIVER_CHARACTERISTICS ; 
 int /*<<< orphan*/  NDIS_SIZEOF_MINIPORT_DRIVER_CHARACTERISTICS_REVISION_2 ; 
 int /*<<< orphan*/  NEO_NDIS_MAJOR_VERSION ; 
 int /*<<< orphan*/  NEO_NDIS_MINOR_VERSION ; 
 scalar_t__ NG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisMRegisterMiniportDriver (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ NeoInit () ; 
 int /*<<< orphan*/  NeoNdisCancelOidRequest ; 
 int /*<<< orphan*/  NeoNdisCancelSend ; 
 int /*<<< orphan*/  NeoNdisCheckForHangEx ; 
 int /*<<< orphan*/  NeoNdisDevicePnPEventNotify ; 
 int /*<<< orphan*/  NeoNdisDriverUnload ; 
 int /*<<< orphan*/  NeoNdisHaltEx ; 
 int /*<<< orphan*/  NeoNdisInitEx ; 
 int /*<<< orphan*/  NeoNdisOidRequest ; 
 int /*<<< orphan*/  NeoNdisPause ; 
 int /*<<< orphan*/  NeoNdisResetEx ; 
 int /*<<< orphan*/  NeoNdisRestart ; 
 int /*<<< orphan*/  NeoNdisReturnNetBufferLists ; 
 int /*<<< orphan*/  NeoNdisSendNetBufferLists ; 
 int /*<<< orphan*/  NeoNdisSetOptions ; 
 int /*<<< orphan*/  NeoNdisShutdownEx ; 
 int /*<<< orphan*/  NeoZero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  PsGetVersion (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int g_is_win8 ; 
 int /*<<< orphan*/  ndis_miniport_driver_handle ; 

NDIS_STATUS DriverEntry(DRIVER_OBJECT *DriverObject, UNICODE_STRING *RegistryPath)
{
	NDIS_MINIPORT_DRIVER_CHARACTERISTICS miniport;
	ULONG os_major_ver = 0, os_minor_ver = 0;
	NDIS_STATUS ret;

	// Initialize the Neo library
	if (NeoInit() == FALSE)
	{
		// Initialization Failed
		return STATUS_UNSUCCESSFUL;
	}

	g_is_win8 = false;

	// Get the OS version
	PsGetVersion(&os_major_ver, &os_minor_ver, NULL, NULL);

	if (os_major_ver >= 7 || (os_major_ver == 6 && os_minor_ver >= 2))
	{
		// Windows 8
		g_is_win8 = true;
	}

	// Register a NDIS miniport driver
	NeoZero(&miniport, sizeof(NDIS_MINIPORT_DRIVER_CHARACTERISTICS));

	miniport.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_DRIVER_CHARACTERISTICS;
	miniport.Header.Revision = NDIS_MINIPORT_DRIVER_CHARACTERISTICS_REVISION_2;
	miniport.Header.Size = NDIS_SIZEOF_MINIPORT_DRIVER_CHARACTERISTICS_REVISION_2;

	miniport.MajorNdisVersion = NEO_NDIS_MAJOR_VERSION;
	miniport.MinorNdisVersion = NEO_NDIS_MINOR_VERSION;

	// Register the handler
	miniport.InitializeHandlerEx = NeoNdisInitEx;
	miniport.HaltHandlerEx = NeoNdisHaltEx;
	miniport.OidRequestHandler = NeoNdisOidRequest;
	miniport.ResetHandlerEx = NeoNdisResetEx;
	miniport.CheckForHangHandlerEx = NeoNdisCheckForHangEx;
	miniport.UnloadHandler = NeoNdisDriverUnload;
	miniport.SendNetBufferListsHandler = NeoNdisSendNetBufferLists;

	miniport.SetOptionsHandler = NeoNdisSetOptions;
	miniport.PauseHandler = NeoNdisPause;
	miniport.RestartHandler = NeoNdisRestart;
	miniport.ReturnNetBufferListsHandler = NeoNdisReturnNetBufferLists;
	miniport.CancelSendHandler = NeoNdisCancelSend;
	miniport.DevicePnPEventNotifyHandler = NeoNdisDevicePnPEventNotify;
	miniport.ShutdownHandlerEx = NeoNdisShutdownEx;
	miniport.CancelOidRequestHandler = NeoNdisCancelOidRequest;

	ret = NdisMRegisterMiniportDriver(DriverObject, RegistryPath,
		NULL, &miniport, &ndis_miniport_driver_handle);

	if (NG(ret))
	{
		// Registration failure
		return STATUS_UNSUCCESSFUL;
	}

	// Initialization success
	return STATUS_SUCCESS;
}