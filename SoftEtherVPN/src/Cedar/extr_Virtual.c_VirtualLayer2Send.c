#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Cancel; int /*<<< orphan*/  SendQueue; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
typedef  void UCHAR ;
struct TYPE_5__ {void* DestAddress; void* SrcAddress; int /*<<< orphan*/  Protocol; } ;
typedef  TYPE_2__ MAC_HEADER ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (void*,void*,int) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_HEADER_SIZE ; 
 int MAX_PACKET_SIZE ; 
 void* Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewBlock (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

void VirtualLayer2Send(VH *v, UCHAR *dest_mac, UCHAR *src_mac, USHORT protocol, void *data, UINT size)
{
	MAC_HEADER *mac_header;
	UCHAR *buf;
	BLOCK *block;
	// Validate arguments
	if (v == NULL || dest_mac == NULL || src_mac == NULL || data == NULL || size > (MAX_PACKET_SIZE - sizeof(MAC_HEADER)))
	{
		return;
	}

	// Create buffer 
	buf = Malloc(MAC_HEADER_SIZE + size);

	// MAC header
	mac_header = (MAC_HEADER *)&buf[0];
	Copy(mac_header->DestAddress, dest_mac, 6);
	Copy(mac_header->SrcAddress, src_mac, 6);
	mac_header->Protocol = Endian16(protocol);

	// Copy data
	Copy(&buf[sizeof(MAC_HEADER)], data, size);

	// Size
	size += sizeof(MAC_HEADER);

	// Generate the packet 
	block = NewBlock(buf, size, 0);

	// Insert into the queue
	LockQueue(v->SendQueue);
	{
		InsertQueue(v->SendQueue, block);
	}
	UnlockQueue(v->SendQueue);

	// Cancel
	Cancel(v->Cancel);
}