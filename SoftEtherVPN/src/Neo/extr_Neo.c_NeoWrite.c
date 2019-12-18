#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  NumPacketRecv; } ;
struct TYPE_7__ {scalar_t__ Halting; scalar_t__ Opened; int /*<<< orphan*/  PacketBufferArray; int /*<<< orphan*/  NdisMiniport; TYPE_1__ Status; TYPE_2__** PacketBuffer; } ;
struct TYPE_6__ {scalar_t__ Buf; int /*<<< orphan*/  NdisPacket; int /*<<< orphan*/  NdisBuffer; } ;
typedef  TYPE_2__ PACKET_BUFFER ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NDIS_SET_PACKET_HEADER_SIZE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NDIS_SET_PACKET_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDIS_STATUS_RESOURCES ; 
 void* NEO_ADDR_OF_PACKET (void*,scalar_t__) ; 
 scalar_t__ NEO_MAX_PACKET_EXCHANGE ; 
 scalar_t__ NEO_MAX_PACKET_SIZE ; 
 scalar_t__ NEO_NUM_PACKET (void*) ; 
 scalar_t__ NEO_PACKET_HEADER_SIZE ; 
 scalar_t__ NEO_SIZE_OF_PACKET (void*,scalar_t__) ; 
 int /*<<< orphan*/  NdisAdjustBufferLength (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NdisMEthIndicateReceive (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  NdisMEthIndicateReceiveComplete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisMIndicateReceivePacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NeoCopy (scalar_t__,void*,scalar_t__) ; 
 TYPE_3__* ctx ; 
 int g_is_win8 ; 

void NeoWrite(void *buf)
{
	UINT num, i, size;
	void *packet_buf;
	// Validate arguments
	if (buf == NULL)
	{
		return;
	}

	// Number of packets
	num = NEO_NUM_PACKET(buf);
	if (num > NEO_MAX_PACKET_EXCHANGE)
	{
		// Number of packets is too many
		return;
	}
	if (num == 0)
	{
		// No packet
		return;
	}

	if (ctx->Halting != FALSE)
	{
		// Halting
		return;
	}

	if (ctx->Opened == FALSE)
	{
		// Not connected
		return;
	}

	for (i = 0;i < num;i++)
	{
		PACKET_BUFFER *p = ctx->PacketBuffer[i];

		size = NEO_SIZE_OF_PACKET(buf, i);
		if (size > NEO_MAX_PACKET_SIZE)
		{
			size = NEO_MAX_PACKET_SIZE;
		}
		if (size < NEO_PACKET_HEADER_SIZE)
		{
			size = NEO_PACKET_HEADER_SIZE;
		}

		packet_buf = NEO_ADDR_OF_PACKET(buf, i);

		// Buffer copy
		NeoCopy(p->Buf, packet_buf, size);

		if (g_is_win8 == false)
		{
			// Adjust the buffer size
			NdisAdjustBufferLength(p->NdisBuffer, size);
			// Set the packet information
			NDIS_SET_PACKET_STATUS(p->NdisPacket, NDIS_STATUS_RESOURCES);
			NDIS_SET_PACKET_HEADER_SIZE(p->NdisPacket, NEO_PACKET_HEADER_SIZE);
		}
		else
		{
			NdisMEthIndicateReceive(ctx->NdisMiniport, ctx, 
				p->Buf, NEO_PACKET_HEADER_SIZE,
				((UCHAR *)p->Buf) + NEO_PACKET_HEADER_SIZE, size - NEO_PACKET_HEADER_SIZE,
				size - NEO_PACKET_HEADER_SIZE);
			NdisMEthIndicateReceiveComplete(ctx->NdisMiniport);
		}
	}

	// Notify that packets have received
	ctx->Status.NumPacketRecv += num;

	if (g_is_win8 == false)
	{
		NdisMIndicateReceivePacket(ctx->NdisMiniport, ctx->PacketBufferArray, num);
	}
}