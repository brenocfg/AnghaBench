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
typedef  size_t UINT ;
struct TYPE_4__ {scalar_t__ Initing; scalar_t__ Inited; int CurrentPacketFilter; struct TYPE_4__* NdisContext; void* NdisMiniport; scalar_t__ ConnectedForce; scalar_t__ ConnectedOld; scalar_t__ Connected; scalar_t__ Halting; int /*<<< orphan*/  HardwareStatus; void* NdisConfig; int /*<<< orphan*/ * NdisWrapper; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  scalar_t__ NDIS_MEDIUM ;
typedef  void* NDIS_HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int NDIS_ATTRIBUTE_DESERIALIZE ; 
 int NDIS_ATTRIBUTE_IGNORE_PACKET_TIMEOUT ; 
 int NDIS_ATTRIBUTE_IGNORE_REQUEST_TIMEOUT ; 
 int NDIS_ATTRIBUTE_NO_HALT_ON_SUSPEND ; 
 int NDIS_PACKET_TYPE_ALL_FUNCTIONAL ; 
 int NDIS_PACKET_TYPE_ALL_LOCAL ; 
 int NDIS_PACKET_TYPE_BROADCAST ; 
 int NDIS_PACKET_TYPE_DIRECTED ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ NEO_MEDIA ; 
 int /*<<< orphan*/  NdisHardwareStatusReady ; 
 int /*<<< orphan*/  NdisInterfaceInternal ; 
 int /*<<< orphan*/  NdisMSetAttributes (void*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisMSetAttributesEx (void*,TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoInitControlDevice () ; 
 int /*<<< orphan*/  NeoInitPacketArray () ; 
 scalar_t__ NeoLoadRegistry () ; 
 int /*<<< orphan*/  NeoSetConnectState (scalar_t__) ; 
 int /*<<< orphan*/  NeoStartAdapter () ; 
 scalar_t__ TRUE ; 
 TYPE_1__* ctx ; 
 int g_is_win8 ; 
 int keep_link ; 
 int /*<<< orphan*/ * ndis_wrapper_handle ; 

NDIS_STATUS NeoNdisInit(NDIS_STATUS *OpenErrorStatus,
					UINT *SelectedMediumIndex,
					NDIS_MEDIUM *MediumArray,
					UINT MediumArraySize,
					NDIS_HANDLE MiniportAdapterHandle,
					NDIS_HANDLE WrapperConfigurationContext)
{
	BOOL media_check;
	UINT i;

	if (ctx == NULL)
	{
		return NDIS_STATUS_FAILURE;
	}

	if (ctx->NdisWrapper == NULL)
	{
		ctx->NdisWrapper = ndis_wrapper_handle;
	}

	// Prevention of multiple start
	if (ctx->Initing != FALSE)
	{
		// Multiple started
		return NDIS_STATUS_FAILURE;
	}
	ctx->Initing = TRUE;

	// Examine whether it has already been initialized
	if (ctx->Inited != FALSE)
	{
		// Driver is started on another instance already.
		// PacketiX VPN driver can start only one instance per one service.
		// User can start multiple drivers with different instance ID
		return NDIS_STATUS_FAILURE;
	}

	// Current value of the packet filter
	ctx->CurrentPacketFilter = NDIS_PACKET_TYPE_ALL_LOCAL | NDIS_PACKET_TYPE_BROADCAST | NDIS_PACKET_TYPE_DIRECTED | NDIS_PACKET_TYPE_ALL_FUNCTIONAL;

	// Examine whether the Ethernet is available
	media_check = FALSE;
	for (i = 0;i < MediumArraySize;i++)
	{
		if (MediumArray[i] == NEO_MEDIA)
		{
			media_check = TRUE;
			break;
		}
	}
	if (media_check == FALSE)
	{
		// Ethernet is unavailable
		ctx->Initing = FALSE;
		return NDIS_STATUS_FAILURE;
	}

	// Media number to use
	*SelectedMediumIndex = i;

	// Initialize the adapter information
	ctx->NdisMiniport = MiniportAdapterHandle;
	ctx->NdisConfig = WrapperConfigurationContext;
	ctx->NdisContext = ctx;
	ctx->HardwareStatus = NdisHardwareStatusReady;
	ctx->Halting = FALSE;
	ctx->Connected = ctx->ConnectedOld = FALSE;

	if (keep_link == false)
	{
		ctx->ConnectedForce = TRUE;
	}

	// Read the information from the registry
	if (NeoLoadRegistry() == FALSE)
	{
		// Failure
		ctx->Initing = FALSE;
		return NDIS_STATUS_FAILURE;
	}

	// Register the device attributes

	if (g_is_win8 == false)
	{
		NdisMSetAttributes(ctx->NdisMiniport, ctx->NdisContext, FALSE, NdisInterfaceInternal);
	}
	else
	{
		NdisMSetAttributesEx(ctx->NdisMiniport, ctx->NdisContext, 16,
			NDIS_ATTRIBUTE_DESERIALIZE | NDIS_ATTRIBUTE_IGNORE_PACKET_TIMEOUT | NDIS_ATTRIBUTE_IGNORE_REQUEST_TIMEOUT | NDIS_ATTRIBUTE_NO_HALT_ON_SUSPEND,
			NdisInterfaceInternal);
	}

	// Initialize the received packet array
	NeoInitPacketArray();

	// Initialize the control device
	NeoInitControlDevice();

	// Start the adapter
	NeoStartAdapter();

	// Flag setting
	ctx->Initing = FALSE;
	ctx->Inited = TRUE;

	// Notify the connection state
	NeoSetConnectState(FALSE);

	return NDIS_STATUS_SUCCESS;
}