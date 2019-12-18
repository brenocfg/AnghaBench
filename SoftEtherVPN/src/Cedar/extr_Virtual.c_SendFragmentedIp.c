#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int HostMask; int /*<<< orphan*/  HostIP; } ;
typedef  TYPE_1__ VH ;
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_17__ {scalar_t__* MacAddress; } ;
struct TYPE_16__ {int DstIP; scalar_t__ Checksum; scalar_t__ SrcIP; scalar_t__ Protocol; scalar_t__ TimeToLive; scalar_t__* FlagsAndFragmentOffset; void* Identification; void* TotalLength; int /*<<< orphan*/  TypeOfService; scalar_t__ VersionAndHeaderLength; } ;
typedef  TYPE_2__ IPV4_HEADER ;
typedef  TYPE_3__ ARP_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (scalar_t__*,void*,scalar_t__) ; 
 int /*<<< orphan*/  DEFAULT_IP_TOS ; 
 scalar_t__ DEFAULT_IP_TTL ; 
 void* Endian16 (int) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/  IPV4_SET_FLAGS (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_HEADER_LEN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_OFFSET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_VERSION (TYPE_2__*,int) ; 
 int IP_HEADER_SIZE ; 
 int /*<<< orphan*/  InsertIpWaitTable (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__) ; 
 scalar_t__ IpChecksum (TYPE_2__*,int) ; 
 scalar_t__ IsInNetwork (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__* Malloc (scalar_t__) ; 
 TYPE_3__* SearchArpTable (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  SendArp (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  VirtualIpSend (TYPE_1__*,scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__* broadcast ; 

void SendFragmentedIp(VH *v, UINT dest_ip, UINT src_ip, USHORT id, USHORT total_size, USHORT offset, UCHAR protocol, void *data, UINT size, UCHAR *dest_mac, UCHAR ttl)
{
	UCHAR *buf;
	IPV4_HEADER *ip;
	ARP_ENTRY *arp;
	// Validate arguments
	if (v == NULL || data == NULL || size == 0)
	{
		return;
	}

	// Memory allocation
	buf = Malloc(size + IP_HEADER_SIZE);
	ip = (IPV4_HEADER *)&buf[0];

	// IP header construction
	ip->VersionAndHeaderLength = 0;
	IPV4_SET_VERSION(ip, 4);
	IPV4_SET_HEADER_LEN(ip, (IP_HEADER_SIZE / 4));
	ip->TypeOfService = DEFAULT_IP_TOS;
	ip->TotalLength = Endian16((USHORT)(size + IP_HEADER_SIZE));
	ip->Identification = Endian16(id);
	ip->FlagsAndFragmentOffset[0] = ip->FlagsAndFragmentOffset[1] = 0;
	IPV4_SET_OFFSET(ip, (offset / 8));
	if ((offset + size) >= total_size)
	{
		IPV4_SET_FLAGS(ip, 0x00);
	}
	else
	{
		IPV4_SET_FLAGS(ip, 0x01);
	}
	ip->TimeToLive = (ttl == 0 ? DEFAULT_IP_TTL : ttl);
	ip->Protocol = protocol;
	ip->Checksum = 0;
	ip->SrcIP = src_ip;
	ip->DstIP = dest_ip;

	// Checksum calculation
	ip->Checksum = IpChecksum(ip, IP_HEADER_SIZE);

	// Data copy
	Copy(buf + IP_HEADER_SIZE, data, size);

	if (dest_mac == NULL)
	{
		if (ip->DstIP == 0xffffffff ||
			(IsInNetwork(ip->DstIP, v->HostIP, v->HostMask) && (ip->DstIP & (~v->HostMask)) == (~v->HostMask)))
		{
			// Broadcast address
			dest_mac = broadcast;
		}
		else
		{
			// Send an ARP query if the destination MAC address is unknown
			arp = SearchArpTable(v, dest_ip);
			if (arp != NULL)
			{
				dest_mac = arp->MacAddress;
			}
		}
	}
	if (dest_mac != NULL)
	{
		// Send the packet immediately
		VirtualIpSend(v, dest_mac, buf, size + IP_HEADER_SIZE);

		// Packet data may be released
		Free(buf);
	}
	else
	{
		// Because this packet still can not be transferred, add it to the IP waiting table
		InsertIpWaitTable(v, dest_ip, src_ip, buf, size + IP_HEADER_SIZE);

		// Issue an ARP
		SendArp(v, dest_ip);
	}
}