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
struct TYPE_4__ {int /*<<< orphan*/  NdisBuffer; int /*<<< orphan*/  NdisPacket; int /*<<< orphan*/  PacketPool; int /*<<< orphan*/  Buf; int /*<<< orphan*/  BufferPool; } ;
typedef  TYPE_1__ PACKET_BUFFER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_SET_PACKET_HEADER_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEO_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  NEO_PACKET_HEADER_SIZE ; 
 int /*<<< orphan*/  NdisAllocateBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisAllocateBufferPool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NdisAllocatePacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisAllocatePacketPool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisChainBufferAtFront (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoMalloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* NeoZeroMalloc (int) ; 
 int /*<<< orphan*/  PROTOCOL_RESERVED_SIZE_IN_PACKET ; 

PACKET_BUFFER *NeoNewPacketBuffer()
{
	PACKET_BUFFER *p;
	NDIS_STATUS ret;

	// Memory allocation
	p = NeoZeroMalloc(sizeof(PACKET_BUFFER));
	// Memory allocation for packet
	p->Buf = NeoMalloc(NEO_MAX_PACKET_SIZE);
	// Allocate the buffer pool
	NdisAllocateBufferPool(&ret, &p->BufferPool, 1);
	// Allocate the buffer
	NdisAllocateBuffer(&ret, &p->NdisBuffer, p->BufferPool, p->Buf, NEO_MAX_PACKET_SIZE);
	// Secure the packet pool
	NdisAllocatePacketPool(&ret, &p->PacketPool, 1, PROTOCOL_RESERVED_SIZE_IN_PACKET);
	// Secure the packet
	NdisAllocatePacket(&ret, &p->NdisPacket, p->PacketPool);
	NDIS_SET_PACKET_HEADER_SIZE(p->NdisPacket, NEO_PACKET_HEADER_SIZE);
	// Attach the buffer to the packet
	NdisChainBufferAtFront(p->NdisPacket, p->NdisBuffer);

	return p;
}