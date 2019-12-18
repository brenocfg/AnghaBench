#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {scalar_t__ HardwareType; scalar_t__ ProtocolType; int HardwareSize; int ProtocolSize; void* TargetIP; int /*<<< orphan*/ * TargetAddress; void* SrcIP; int /*<<< orphan*/ * SrcAddress; scalar_t__ Operation; } ;
struct TYPE_9__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  ClientIPAddress; int /*<<< orphan*/ * MacAddress; } ;
typedef  TYPE_1__ IPC ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ BLOCK ;
typedef  TYPE_3__ ARPV4_HEADER ;

/* Variables and functions */
 scalar_t__ ARP_HARDWARE_TYPE_ETHERNET ; 
 scalar_t__ ARP_OPERATION_REQUEST ; 
 scalar_t__ ARP_OPERATION_RESPONSE ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ Endian16 (scalar_t__) ; 
 int /*<<< orphan*/  IPCAssociateOnArpTable (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPCSendL2 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 void* IPToUINT (int /*<<< orphan*/ *) ; 
 scalar_t__ IsValidUnicastMacAddress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAC_PROTO_ARPV4 ; 
 scalar_t__ MAC_PROTO_IPV4 ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  WRITE_USHORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void IPCProcessArp(IPC *ipc, BLOCK *b)
{
	UCHAR *dest_mac;
	UCHAR *src_mac;
	ARPV4_HEADER *arp;
	UCHAR *sender_mac;
	IP sender_ip;
	UCHAR *target_mac;
	IP target_ip;
	// Validate arguments
	if (ipc == NULL || b == NULL || b->Size < (14 + sizeof(ARPV4_HEADER)))
	{
		return;
	}

	dest_mac = b->Buf + 0;
	src_mac = b->Buf + 6;

	arp = (ARPV4_HEADER *)(b->Buf + 14);

	if (arp->HardwareType != Endian16(ARP_HARDWARE_TYPE_ETHERNET))
	{
		return;
	}
	if (arp->ProtocolType != Endian16(MAC_PROTO_IPV4))
	{
		return;
	}
	if (arp->HardwareSize != 6 || arp->ProtocolSize != 4)
	{
		return;
	}

	sender_mac = arp->SrcAddress;
	UINTToIP(&sender_ip, arp->SrcIP);

	target_mac = arp->TargetAddress;
	UINTToIP(&target_ip, arp->TargetIP);

	if (CmpIpAddr(&sender_ip, &ipc->ClientIPAddress) == 0)
	{
		// Source is myself
		return;
	}

	IPCAssociateOnArpTable(ipc, &sender_ip, sender_mac);
	IPCAssociateOnArpTable(ipc, &target_ip, target_mac);

	if (Endian16(arp->Operation) == ARP_OPERATION_REQUEST)
	{
		// Received an ARP request
		if (CmpIpAddr(&target_ip, &ipc->ClientIPAddress) == 0)
		{
			// Create a response since a request for its own IP address have received
			if (IsValidUnicastMacAddress(sender_mac))
			{
				UCHAR tmp[14 + sizeof(ARPV4_HEADER)];
				ARPV4_HEADER *arp = (ARPV4_HEADER *)(tmp + 14);

				Copy(tmp + 0, sender_mac, 6);
				Copy(tmp + 6, ipc->MacAddress, 6);
				WRITE_USHORT(tmp + 12, MAC_PROTO_ARPV4);

				arp->HardwareType = Endian16(ARP_HARDWARE_TYPE_ETHERNET);
				arp->ProtocolType = Endian16(MAC_PROTO_IPV4);
				arp->HardwareSize = 6;
				arp->ProtocolSize = 4;
				arp->Operation = Endian16(ARP_OPERATION_RESPONSE);

				Copy(arp->SrcAddress, ipc->MacAddress, 6);
				arp->SrcIP = IPToUINT(&ipc->ClientIPAddress);

				Copy(arp->TargetAddress, sender_mac, 6);
				arp->TargetIP = IPToUINT(&sender_ip);

				IPCSendL2(ipc, tmp, sizeof(tmp));
			}
		}
	}
}