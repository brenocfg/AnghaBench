#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
typedef  void UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  SendQueue; } ;
struct TYPE_8__ {void* DestAddress; void* SrcAddress; int /*<<< orphan*/  Protocol; } ;
struct TYPE_7__ {int PacketSize; void* PacketData; } ;
typedef  TYPE_1__ PKT ;
typedef  TYPE_2__ MAC_HEADER ;
typedef  TYPE_3__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,int) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ MAC_HEADER_SIZE ; 
 void* Malloc (scalar_t__) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void L3SendL2Now(L3IF *f, UCHAR *dest_mac, UCHAR *src_mac, USHORT protocol, void *data, UINT size)
{
	UCHAR *buf;
	MAC_HEADER *mac_header;
	PKT *p;
	// Validate arguments
	if (f == NULL || dest_mac == NULL || src_mac == NULL || data == NULL)
	{
		return;
	}

	// Buffer creation
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

	// Packet generation
	p = ZeroMalloc(sizeof(PKT));
	p->PacketData = buf;
	p->PacketSize = size;

	// Add to the queue
	InsertQueue(f->SendQueue, p);
}