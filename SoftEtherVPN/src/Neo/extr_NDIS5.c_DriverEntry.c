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
struct TYPE_6__ {int /*<<< orphan*/  NdisWrapper; } ;
struct TYPE_5__ {int /*<<< orphan*/ * SendHandler; int /*<<< orphan*/  SendPacketsHandler; int /*<<< orphan*/  SetInformationHandler; int /*<<< orphan*/  ResetHandler; int /*<<< orphan*/  QueryInformationHandler; int /*<<< orphan*/  HaltHandler; int /*<<< orphan*/  InitializeHandler; int /*<<< orphan*/  MinorNdisVersion; int /*<<< orphan*/  MajorNdisVersion; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  TYPE_1__ NDIS_MINIPORT_CHARACTERISTICS ;
typedef  int /*<<< orphan*/  DRIVER_OBJECT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NEO_NDIS_MAJOR_VERSION ; 
 int /*<<< orphan*/  NEO_NDIS_MINOR_VERSION ; 
 scalar_t__ NG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisMInitializeWrapper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisMRegisterMiniport (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ NeoInit () ; 
 int /*<<< orphan*/  NeoNdisHalt ; 
 int /*<<< orphan*/  NeoNdisInit ; 
 int /*<<< orphan*/  NeoNdisQuery ; 
 int /*<<< orphan*/  NeoNdisReset ; 
 int /*<<< orphan*/  NeoNdisSendPackets ; 
 int /*<<< orphan*/  NeoNdisSet ; 
 int /*<<< orphan*/  NeoZero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PsGetVersion (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 TYPE_2__* ctx ; 
 int g_is_win8 ; 
 int /*<<< orphan*/  ndis_wrapper_handle ; 

NDIS_STATUS DriverEntry(DRIVER_OBJECT *DriverObject, UNICODE_STRING *RegistryPath)
{
	NDIS_MINIPORT_CHARACTERISTICS miniport;
	ULONG os_major_ver = 0, os_minor_ver = 0;

	// Initialize the Neo library
	if (NeoInit() == FALSE)
	{
		// Initialization Failed
		return STATUS_UNSUCCESSFUL;
	}

	g_is_win8 = false;

#ifndef	NDIS30_MINIPORT
	// Get the OS version
	PsGetVersion(&os_major_ver, &os_minor_ver, NULL, NULL);

	if (os_major_ver >= 7 || (os_major_ver == 6 && os_minor_ver >= 2))
	{
		// Windows 8
		g_is_win8 = true;
	}
#endif	// NDIS30_MINIPORT

	// Initialize the NDIS wrapper
	NdisMInitializeWrapper(&ctx->NdisWrapper, DriverObject, RegistryPath, NULL);
	ndis_wrapper_handle = ctx->NdisWrapper;

	// Register a NDIS miniport driver
	NeoZero(&miniport, sizeof(NDIS_MINIPORT_CHARACTERISTICS));
	miniport.MajorNdisVersion = NEO_NDIS_MAJOR_VERSION;
	miniport.MinorNdisVersion = NEO_NDIS_MINOR_VERSION;

	// Register the handler
	miniport.InitializeHandler = NeoNdisInit;
	miniport.HaltHandler = NeoNdisHalt;
	miniport.QueryInformationHandler = NeoNdisQuery;
	miniport.ResetHandler = NeoNdisReset;
	miniport.SetInformationHandler = NeoNdisSet;

#ifndef	NDIS30_MINIPORT
	miniport.SendPacketsHandler = NeoNdisSendPackets;
#else	// NDIS30_MINIPORT
	miniport.SendHandler = NULL;
#endif	// NDIS30_MINIPORT

	if (NG(NdisMRegisterMiniport(ctx->NdisWrapper, &miniport, sizeof(NDIS_MINIPORT_CHARACTERISTICS))))
	{
		// Registration failure
		return STATUS_UNSUCCESSFUL;
	}

	// Initialization success
	return STATUS_SUCCESS;
}