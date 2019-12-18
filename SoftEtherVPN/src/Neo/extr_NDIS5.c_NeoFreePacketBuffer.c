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
struct TYPE_4__ {int /*<<< orphan*/  BufferPool; struct TYPE_4__* Buf; int /*<<< orphan*/  NdisBuffer; int /*<<< orphan*/  PacketPool; int /*<<< orphan*/  NdisPacket; } ;
typedef  TYPE_1__ PACKET_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  NdisFreeBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreeBufferPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreePacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreePacketPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisUnchainBufferAtFront (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoFree (TYPE_1__*) ; 

void NeoFreePacketBuffer(PACKET_BUFFER *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	// Detach the buffer from the packet
	NdisUnchainBufferAtFront(p->NdisPacket, &p->NdisBuffer);
	// Release the packet
	NdisFreePacket(p->NdisPacket);
	// Release the packet pool
	NdisFreePacketPool(p->PacketPool);
	// Release the buffer
	NdisFreeBuffer(p->NdisBuffer);
	// Release the memory
	NeoFree(p->Buf);
	// Release the buffer pool
	NdisFreeBufferPool(p->BufferPool);
	// Release the memory
	NeoFree(p);
}