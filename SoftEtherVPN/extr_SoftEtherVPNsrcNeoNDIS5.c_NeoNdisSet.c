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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  CurrentPacketFilter; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  int NDIS_OID ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_OID ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
#define  OID_802_3_MULTICAST_LIST 130 
#define  OID_GEN_CURRENT_LOOKAHEAD 129 
#define  OID_GEN_CURRENT_PACKET_FILTER 128 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 TYPE_1__* ctx ; 

NDIS_STATUS NeoNdisSet(
					NDIS_HANDLE MiniportAdapterContext,
					NDIS_OID Oid,
					void *InformationBuffer,
					ULONG InformationBufferLength,
					ULONG *BytesRead,
					ULONG *BytesNeeded)
{
	if (ctx == NULL)
	{
		return STATUS_UNSUCCESSFUL;
	}

	// Initialization
	*BytesRead = 0;
	*BytesNeeded = 0;

	// Branch processing
	switch (Oid)
	{
	case OID_GEN_CURRENT_PACKET_FILTER:
		/* Packet filter */
		if (InformationBufferLength != 4)
		{
			*BytesNeeded = 4;
			return NDIS_STATUS_INVALID_LENGTH;
		}
		*BytesRead = 4;
		ctx->CurrentPacketFilter = *((UINT *)InformationBuffer);
		return NDIS_STATUS_SUCCESS;

//	case OID_GEN_PROTOCOL_OPTIONS:
		/* Current protocol option value */
/*		if (InformationBufferLength != 4)
		{
			*BytesNeeded = 4;
			return NDIS_STATUS_INVALID_LENGTH;
		}
		*BytesRead = 4;
		ctx->CurrentProtocolOptions = *((UINT *)InformationBuffer);
		return NDIS_STATUS_SUCCESS;*/

	case OID_GEN_CURRENT_LOOKAHEAD:
		/* Look ahead */
		if (InformationBufferLength != 4)
		{
			*BytesNeeded = 4;
			return NDIS_STATUS_INVALID_LENGTH;
		}
		*BytesRead = 4;
		return NDIS_STATUS_SUCCESS;

	case OID_802_3_MULTICAST_LIST:
		// Multicast list
		*BytesRead = InformationBufferLength;

		return NDIS_STATUS_SUCCESS;
	}

	return NDIS_STATUS_INVALID_OID;
}