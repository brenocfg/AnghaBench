#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/  NumPacketSendError; } ;
struct TYPE_4__ {scalar_t__ Halting; scalar_t__ Opened; TYPE_1__ Status; int /*<<< orphan*/  NdisMiniport; } ;
typedef  int /*<<< orphan*/  NDIS_PACKET ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NDIS_SET_PACKET_STATUS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NdisMSendComplete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 TYPE_2__* ctx ; 
 scalar_t__ g_is_win8 ; 

BOOL NeoNdisSendPacketsHaltCheck(NDIS_PACKET **PacketArray, UINT NumberOfPackets)
{
	UINT i;

	if (ctx == NULL)
	{
		return FALSE;
	}

	if (ctx->Halting != FALSE || ctx->Opened == FALSE)
	{
		// Finishing
		for (i = 0;i < NumberOfPackets;i++)
		{
			NDIS_SET_PACKET_STATUS(PacketArray[i], NDIS_STATUS_FAILURE);

			if (g_is_win8)
			{
				NdisMSendComplete(ctx->NdisMiniport, PacketArray[i], NDIS_STATUS_SUCCESS);
			}

			ctx->Status.NumPacketSendError++;
		}
		return FALSE;
	}
	return TRUE;
}