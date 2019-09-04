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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  NumPacketSend; int /*<<< orphan*/  NumPacketSendError; } ;
struct TYPE_4__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  NdisMiniport; TYPE_1__ Status; } ;
typedef  scalar_t__ PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  NDIS_PACKET ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NDIS_SET_PACKET_STATUS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ NEO_MAX_PACKET_SIZE ; 
 scalar_t__ NEO_MIN_PACKET_SIZE ; 
 int /*<<< orphan*/  NdisGetNextBuffer (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  NdisMSendComplete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisQueryBuffer (scalar_t__,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  NdisQueryPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  NeoCheckConnectState () ; 
 int /*<<< orphan*/  NeoCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  NeoFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoInsertQueue (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  NeoLockPacketQueue () ; 
 int /*<<< orphan*/ * NeoMalloc (scalar_t__) ; 
 scalar_t__ NeoNdisSendPacketsHaltCheck (int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  NeoSet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoUnlockPacketQueue () ; 
 TYPE_2__* ctx ; 
 scalar_t__ g_is_win8 ; 

void NeoNdisSendPackets(NDIS_HANDLE MiniportAdapterContext,
						NDIS_PACKET **PacketArray,
						UINT NumberOfPackets)
{
	UCHAR *Buf,*BufCopy;
	PNDIS_BUFFER Buffer;
	UCHAR *Tmp;
	UINT PacketLength;
	UINT CurrentLength;
	UINT i;

	if (ctx == NULL)
	{
		return;
	}

	// Update the connection state
	NeoCheckConnectState();

	if (NumberOfPackets == 0)
	{
		// The number of packets is 0
		return;
	}

	if (NeoNdisSendPacketsHaltCheck(PacketArray, NumberOfPackets) == FALSE)
	{
		// Device is stopped
		return;
	}

	// Operation of the packet queue
	NeoLockPacketQueue();
	{
		if (NeoNdisSendPacketsHaltCheck(PacketArray, NumberOfPackets) == FALSE)
		{
			// Device is stopped
			NeoUnlockPacketQueue();
			return;
		}

		// Place the packet in the queue in order
		for (i = 0;i < NumberOfPackets;i++)
		{
			// Get a packet
			NdisQueryPacket(PacketArray[i], NULL, NULL, &Buffer, &PacketLength);

			// Extract the packet.
			// Memory allocated here is used for the queue and is released at the time of releasing the queue.
			Buf = NeoMalloc(PacketLength);
			BufCopy = Buf;
			while (Buffer)
			{
				NdisQueryBuffer(Buffer, &Tmp, &CurrentLength);
				if (CurrentLength == 0)
				{
					// Complete
					break;
				}
				NeoCopy(BufCopy, Tmp, CurrentLength);
				BufCopy += CurrentLength;
				NdisGetNextBuffer(Buffer, &Buffer);
			}
			// Process this packet
			if (PacketLength > NEO_MIN_PACKET_SIZE)
			{
				if (PacketLength > NEO_MAX_PACKET_SIZE)
				{
					// Packet is too large
					NDIS_SET_PACKET_STATUS(PacketArray[i], NDIS_STATUS_FAILURE);

					if (g_is_win8)
					{
						NdisMSendComplete(ctx->NdisMiniport, PacketArray[i], NDIS_STATUS_FAILURE);
					}

					ctx->Status.NumPacketSendError++;
					NeoFree(Buf);
				}
				else
				{
					// Insert the packet into the queue
					NeoInsertQueue(Buf, PacketLength);
					NDIS_SET_PACKET_STATUS(PacketArray[i], NDIS_STATUS_SUCCESS);

					if (g_is_win8)
					{
						NdisMSendComplete(ctx->NdisMiniport, PacketArray[i], NDIS_STATUS_SUCCESS);
					}

					ctx->Status.NumPacketSend++;
				}
			}
			else
			{
				// Release if the packet doesn't contain data
				NDIS_SET_PACKET_STATUS(PacketArray[i], NDIS_STATUS_SUCCESS);

				if (g_is_win8)
				{
					NdisMSendComplete(ctx->NdisMiniport, PacketArray[i], NDIS_STATUS_SUCCESS);
				}

				NeoFree(Buf);
			}
		}
	}
	NeoUnlockPacketQueue();

	// Reception event
	NeoSet(ctx->Event);
}