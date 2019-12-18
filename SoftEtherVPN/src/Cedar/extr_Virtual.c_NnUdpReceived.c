#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_9__ {int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  DstPort; int /*<<< orphan*/  PacketLength; } ;
typedef  TYPE_1__ UDP_HEADER ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  Now; } ;
struct TYPE_11__ {TYPE_4__* v; int /*<<< orphan*/  NatTableForRecv; } ;
struct TYPE_10__ {int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  SrcIp; int /*<<< orphan*/  TotalRecv; int /*<<< orphan*/  LastCommTime; } ;
typedef  TYPE_2__ NATIVE_NAT_ENTRY ;
typedef  TYPE_3__ NATIVE_NAT ;

/* Variables and functions */
 int Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAT_UDP ; 
 int /*<<< orphan*/  NnSetNat (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* SearchHash (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SendUdp (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 

void NnUdpReceived(NATIVE_NAT *t, UINT src_ip, UINT dest_ip, void *data, UINT size, UCHAR ttl, UINT max_l3_size)
{
	UDP_HEADER *udp;
	UCHAR *payload;
	UINT payload_size;
	// Validate arguments
	if (t == NULL || data == NULL)
	{
		return;
	}

	// UDP header
	if (size <= sizeof(UDP_HEADER))
	{
		return;
	}

	udp = (UDP_HEADER *)data;

	// Payload
	payload = ((UCHAR *)data) + sizeof(UDP_HEADER);
	payload_size = size - sizeof(UDP_HEADER);

	// Inspect the payload size
	if (payload_size < (Endian16(udp->PacketLength) - sizeof(UDP_HEADER)))
	{
		return;
	}

	// Truncate the payload
	payload_size = Endian16(udp->PacketLength) - sizeof(UDP_HEADER);

	// Search the port number from the NAT table
	if (true)
	{
		NATIVE_NAT_ENTRY tt;
		NATIVE_NAT_ENTRY *e;

		NnSetNat(&tt, NAT_UDP, 0, 0, 0, 0, dest_ip, Endian16(udp->DstPort));

		e = SearchHash(t->NatTableForRecv, &tt);

		if (e != NULL)
		{
			// Last communication time
			e->LastCommTime = t->v->Now;
			e->TotalRecv += (UINT64)payload_size;

			// Deliver to the client by rewriting the port number
			SendUdp(t->v, e->SrcIp, e->SrcPort, src_ip, Endian16(udp->SrcPort),
				payload, payload_size);
		}
	}
}