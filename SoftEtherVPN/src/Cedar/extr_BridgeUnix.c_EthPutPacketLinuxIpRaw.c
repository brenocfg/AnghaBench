#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_23__ {int DstIP; scalar_t__ SrcIP; scalar_t__ Checksum; } ;
typedef  TYPE_4__ UCHAR ;
struct TYPE_26__ {int /*<<< orphan*/  MyPhysicalIP; int /*<<< orphan*/  YourIP; TYPE_5__* RawIcmp; TYPE_5__* RawUdp; TYPE_5__* RawTcp; int /*<<< orphan*/  RawIpMyMacAddr; int /*<<< orphan*/  RawIpYourMacAddr; scalar_t__ RawIp_HasError; } ;
struct TYPE_22__ {TYPE_4__* IPv4Header; } ;
struct TYPE_21__ {TYPE_18__* TCPHeader; TYPE_1__* UDPHeader; } ;
struct TYPE_25__ {int BroadcastPacket; scalar_t__ TypeL3; scalar_t__ TypeL4; int PacketSize; TYPE_4__* PacketData; TYPE_3__ L3; int /*<<< orphan*/  IPv4PayloadSize; TYPE_2__ L4; TYPE_4__* IPv4PayloadData; int /*<<< orphan*/  MacAddressDest; int /*<<< orphan*/  MacAddressSrc; } ;
struct TYPE_24__ {int RawIP_HeaderIncludeFlag; } ;
struct TYPE_20__ {scalar_t__ Checksum; } ;
struct TYPE_19__ {scalar_t__ Checksum; } ;
typedef  TYPE_5__ SOCK ;
typedef  TYPE_6__ PKT ;
typedef  TYPE_4__ IPV4_HEADER ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_8__ ETH ;

/* Variables and functions */
 scalar_t__ CalcChecksumForIPv4 (scalar_t__,int,int /*<<< orphan*/ ,TYPE_18__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EthProcessIpPacketInnerIpRaw (TYPE_8__*,TYPE_6__*) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreePacket (TYPE_6__*) ; 
 scalar_t__ IPToUINT (int /*<<< orphan*/ *) ; 
 int IPV4_GET_HEADER_LEN (TYPE_4__*) ; 
 int /*<<< orphan*/  IP_PROTO_TCP ; 
 scalar_t__ IpChecksum (TYPE_4__*,int) ; 
 int IsValidUnicastMacAddress (int /*<<< orphan*/ ) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,int) ; 
 int IsZeroIP (int /*<<< orphan*/ *) ; 
 scalar_t__ L3_ARPV4 ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L4_FRAGMENT ; 
 scalar_t__ L4_ICMPV4 ; 
 scalar_t__ L4_TCP ; 
 scalar_t__ L4_UDP ; 
 int MAX_PACKET_SIZE ; 
 TYPE_6__* ParsePacket (void*,int) ; 
 int /*<<< orphan*/  SendTo (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int) ; 

void EthPutPacketLinuxIpRaw(ETH *e, void *data, UINT size)
{
	PKT *p;
	SOCK *s = NULL;
	// Validate arguments
	if (e == NULL || data == NULL)
	{
		return;
	}
	if (size < 14 || size > MAX_PACKET_SIZE || e->RawIp_HasError)
	{
		Free(data);
		return;
	}

	p = ParsePacket(data, size);
	if (p == NULL)
	{
		Free(data);
		return;
	}

	if (p->BroadcastPacket || Cmp(p->MacAddressDest, e->RawIpMyMacAddr, 6) == 0)
	{
		if (IsValidUnicastMacAddress(p->MacAddressSrc))
		{
			Copy(e->RawIpYourMacAddr, p->MacAddressSrc, 6);
		}
	}

	if (IsZero(e->RawIpYourMacAddr, 6) || IsValidUnicastMacAddress(p->MacAddressSrc) == false ||
		(p->BroadcastPacket == false && Cmp(p->MacAddressDest, e->RawIpMyMacAddr, 6) != 0))
	{
		Free(data);
		FreePacket(p);
		return;
	}


	if (p->TypeL3 == L3_IPV4)
	{
		if (p->TypeL4 == L4_TCP)
		{
			if (IsZeroIP(&e->MyPhysicalIP) == false)
			{
				s = e->RawTcp;
			}
		}
		else if (p->TypeL4 == L4_UDP)
		{
			if (EthProcessIpPacketInnerIpRaw(e, p) == false)
			{
				s = e->RawUdp;
			}
		}
		else if (p->TypeL4 == L4_ICMPV4)
		{
			if (IsZeroIP(&e->MyPhysicalIP) == false)
			{
				s = e->RawIcmp;
			}
		}
		else if (p->TypeL4 == L4_FRAGMENT)
		{
			if (IsZeroIP(&e->MyPhysicalIP) == false)
			{
				s = e->RawIcmp;
			}
		}
	}
	else if (p->TypeL3 == L3_ARPV4)
	{
		EthProcessIpPacketInnerIpRaw(e, p);
	}

	if (s != NULL && p->L3.IPv4Header->DstIP != 0xffffffff && p->BroadcastPacket == false &&
		p->L3.IPv4Header->SrcIP == IPToUINT(&e->YourIP))
	{
		UCHAR *send_data = p->IPv4PayloadData;
		UCHAR *head = p->PacketData;
		UINT remove_header_size = (UINT)(send_data - head);

		if (p->PacketSize > remove_header_size)
		{
			IP dest;
			UINT send_data_size = p->PacketSize - remove_header_size;

			// checksum
			if (p->TypeL4 == L4_UDP)
			{
				p->L4.UDPHeader->Checksum = 0;
			}
			else if (p->TypeL4 == L4_TCP)
			{
				p->L4.TCPHeader->Checksum = 0;
				p->L4.TCPHeader->Checksum = CalcChecksumForIPv4(IPToUINT(&e->MyPhysicalIP),
					p->L3.IPv4Header->DstIP, IP_PROTO_TCP,
					p->L4.TCPHeader, p->IPv4PayloadSize, 0);
			}

			UINTToIP(&dest, p->L3.IPv4Header->DstIP);

			if (s->RawIP_HeaderIncludeFlag == false)
			{
				SendTo(s, &dest, 0, send_data, send_data_size);
			}
			else
			{
				IPV4_HEADER *ip = p->L3.IPv4Header;

				ip->SrcIP = IPToUINT(&e->MyPhysicalIP);
				ip->Checksum = 0;
				ip->Checksum = IpChecksum(ip, IPV4_GET_HEADER_LEN(ip) * 4);

				SendTo(s, &dest, 0, ip, ((UCHAR *)p->PacketData - (UCHAR *)ip) + p->PacketSize);
			}
		}
	}

	FreePacket(p);
	Free(data);
}