#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_20__ {int Size; int* Buf; } ;
struct TYPE_19__ {int* addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  IPv4ReceivedQueue; TYPE_2__ ClientIPAddress; TYPE_2__ BroadcastAddress; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ IPC ;
typedef  TYPE_2__ IP ;
typedef  TYPE_3__ BLOCK ;

/* Variables and functions */
 int* Clone (int*,int) ; 
 scalar_t__ Cmp (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CmpIpAddr (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (int*) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_3__*) ; 
 int /*<<< orphan*/  IPCAssociateOnArpTable (TYPE_1__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  IPCFlushArpTableEx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPCProcessArp (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  IPCProcessInterrupts (TYPE_1__*) ; 
 TYPE_3__* IPCRecvL2 (TYPE_1__*) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsValidUnicastMacAddress (int*) ; 
 scalar_t__ IsZeroIP (TYPE_2__*) ; 
 scalar_t__ MAC_PROTO_ARPV4 ; 
 scalar_t__ MAC_PROTO_IPV4 ; 
 int /*<<< orphan*/  NewBlock (int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ READ_USHORT (int*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  UINTToIP (TYPE_2__*,int) ; 

void IPCProcessL3EventsEx(IPC *ipc, UINT64 now)
{
	// Validate arguments
	if (ipc == NULL)
	{
		return;
	}
	if (now == 0)
	{
		now = Tick64();
	}

	// Remove old ARP table entries
	IPCFlushArpTableEx(ipc, now);

	// Receive all the L2 packet
	while (true)
	{
		BLOCK *b = IPCRecvL2(ipc);
		if (b == NULL)
		{
			// All reception completed
			break;
		}

		if (b->Size >= 14)
		{
			UCHAR *dest_mac = b->Buf + 0;
			UCHAR *src_mac = b->Buf + 6;
			USHORT protocol = READ_USHORT(b->Buf + 12);

			// Confirm the destination MAC address
			// (Receive if the destination MAC address is the IPC address or a broadcast address)
			if (Cmp(dest_mac, ipc->MacAddress, 6) == 0 || dest_mac[0] & 0x01)
			{
				// If the source MAC address is itselves or invalid address, ignore the packet
				if (Cmp(src_mac, ipc->MacAddress, 6) != 0 && IsValidUnicastMacAddress(src_mac))
				{
					if (protocol == MAC_PROTO_ARPV4)
					{
						// ARP receiving process
						IPCProcessArp(ipc, b);
					}
					else if (protocol == MAC_PROTO_IPV4)
					{
						// IPv4 receiving process
						if (b->Size >= (14 + 20))
						{
							UCHAR *data = Clone(b->Buf + 14, b->Size - 14);
							UINT size = b->Size - 14;
							IP ip_src, ip_dst;
							bool ok = false;

							// Extract the IP address portion
							UINTToIP(&ip_src, *((UINT *)(((UCHAR *)data) + 12)));
							UINTToIP(&ip_dst, *((UINT *)(((UCHAR *)data) + 16)));

							// Receive only if the IPv4 destination address is its own
							// or 255.255.255.255 or a multicast address or a broadcast address
							if (CmpIpAddr(&ip_dst, &ipc->ClientIPAddress) == 0)
							{
								ok = true;
							}
							else if (ip_dst.addr[0] == 255 && ip_dst.addr[1] == 255 &&
								ip_dst.addr[2] == 255 && ip_dst.addr[3] == 255)
							{
								ok = true;
							}
							else if (ip_dst.addr[0] >= 224 && ip_dst.addr[0] <= 239)
							{
								ok = true;
							}
							else
							{
								if (CmpIpAddr(&ipc->BroadcastAddress, &ip_dst) == 0)
								{
									ok = true;
								}

								if (IsZeroIP(&ipc->ClientIPAddress))
								{
									// Client IP address is undetermined
									ok = true;
								}
							}

							if (ok)
							{
								IPCAssociateOnArpTable(ipc, &ip_src, src_mac);

								// Place in the reception queue
								InsertQueue(ipc->IPv4ReceivedQueue, NewBlock(data, size, 0));
							}
							else
							{
								// This packet is discarded because it is irrelevant for me
								Free(data);
							}
						}
					}
				}
			}
		}

		FreeBlock(b);
	}

	IPCProcessInterrupts(ipc);
}