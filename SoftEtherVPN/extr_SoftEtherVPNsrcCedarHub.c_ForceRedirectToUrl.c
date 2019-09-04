#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v6 ;
typedef  int /*<<< orphan*/  v4 ;
typedef  int USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_41__ {TYPE_7__* PacketAdapter; } ;
struct TYPE_40__ {int Size; int Flag; int TimeToLive; int HopLimit; int /*<<< orphan*/ * Buf; int /*<<< orphan*/  DestAddress; int /*<<< orphan*/  SrcAddress; void* NextHeader; void* PayloadLength; int /*<<< orphan*/  Checksum; int /*<<< orphan*/  DstIP; int /*<<< orphan*/  SrcIP; void* Protocol; void* Identification; void* TotalLength; void* WindowSize; scalar_t__ SeqNumber; scalar_t__ AckNumber; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  DstPort; } ;
struct TYPE_39__ {scalar_t__ Param; } ;
struct TYPE_38__ {TYPE_5__* IPv6Header; } ;
struct TYPE_37__ {int /*<<< orphan*/  SrcAddress; int /*<<< orphan*/  DestAddress; } ;
struct TYPE_36__ {TYPE_3__* IPv4Header; } ;
struct TYPE_35__ {int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  DstIP; } ;
struct TYPE_34__ {TYPE_8__ Protocol; TYPE_8__* DestAddress; TYPE_8__* SrcAddress; } ;
struct TYPE_33__ {TYPE_8__* TCPHeader; } ;
struct TYPE_32__ {scalar_t__ TypeL3; scalar_t__ TypeL4; TYPE_6__ IPv6HeaderPacketInfo; TYPE_4__ L3; TYPE_2__* MacHeader; scalar_t__ PayloadSize; TYPE_1__ L4; } ;
typedef  TYPE_8__ TCP_HEADER ;
typedef  TYPE_9__ SESSION ;
typedef  TYPE_10__ PKT ;
typedef  TYPE_8__ IPV6_HEADER ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  TYPE_8__ IPV4_HEADER ;
typedef  int /*<<< orphan*/  HUB_PA ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_8__ BUF ;

/* Variables and functions */
 TYPE_8__* BuildRedirectToUrlPayload (int /*<<< orphan*/ *,TYPE_9__*,char*) ; 
 int /*<<< orphan*/  CalcChecksumForIPv4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CalcChecksumForIPv6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* Endian16 (int) ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_8__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_8__*) ; 
 int /*<<< orphan*/  IPV4_SET_FLAGS (TYPE_8__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_HEADER_LEN (TYPE_8__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_VERSION (TYPE_8__*,int) ; 
 int /*<<< orphan*/  IPV6_SET_VERSION (TYPE_8__*,int) ; 
 void* IP_PROTO_TCP ; 
 int /*<<< orphan*/  IpChecksum (TYPE_8__*,int) ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L3_IPV6 ; 
 scalar_t__ L4_TCP ; 
 TYPE_8__* NewBuf () ; 
 int Rand16 () ; 
 int /*<<< orphan*/  StorePacketToHubPa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int TCP_ACK ; 
 int TCP_PSH ; 
 int /*<<< orphan*/  TCP_SET_HEADER_SIZE (TYPE_8__*,int) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_8__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_8__*,int) ; 
 scalar_t__ ZeroMalloc (int) ; 

void ForceRedirectToUrl(HUB *hub, SESSION *src_session, PKT *p, char *redirect_url)
{
	BUF *payload;
	UINT tcp_size;
	TCP_HEADER *tcp_data;
	TCP_HEADER *src_tcp;
	BUF *b;
	// Validate arguments
	if (hub == NULL || src_session == NULL || p == NULL || redirect_url == NULL)
	{
		return;
	}
	if (p->TypeL3 != L3_IPV4 && p->TypeL3 != L3_IPV6)
	{
		return;
	}
	if (p->TypeL4 != L4_TCP)
	{
		return;
	}

	src_tcp = p->L4.TCPHeader;
	if (src_tcp == NULL)
	{
		return;
	}

	// Generate a payload to be sent
	payload = BuildRedirectToUrlPayload(hub, src_session, redirect_url);
	if (payload == NULL)
	{
		return;
	}

	// Generate a TCP packet
	tcp_size = sizeof(TCP_HEADER) + payload->Size;
	tcp_data = (TCP_HEADER *)ZeroMalloc(tcp_size);
	tcp_data->SrcPort = src_tcp->DstPort;
	tcp_data->DstPort = src_tcp->SrcPort;
	tcp_data->SeqNumber = src_tcp->AckNumber;
	tcp_data->AckNumber = Endian32(Endian32(src_tcp->SeqNumber) + p->PayloadSize);
	TCP_SET_HEADER_SIZE(tcp_data, 5);
	tcp_data->Flag = TCP_ACK | TCP_PSH;
	tcp_data->WindowSize = Endian16(0xFFFF);
	Copy(((UCHAR *)tcp_data) + sizeof(TCP_HEADER), payload->Buf, payload->Size);

	// Calculate the TCP checksum
	if (p->TypeL3 == L3_IPV4)
	{
		// IPv4
		tcp_data->Checksum = CalcChecksumForIPv4(p->L3.IPv4Header->DstIP, p->L3.IPv4Header->SrcIP, IP_PROTO_TCP,
			tcp_data, tcp_size, 0);
	}
	else
	{
		// IPv6
		tcp_data->Checksum = CalcChecksumForIPv6(&p->IPv6HeaderPacketInfo.IPv6Header->DestAddress,
			&p->IPv6HeaderPacketInfo.IPv6Header->SrcAddress, IP_PROTO_TCP, tcp_data, tcp_size, 0);
	}

	// Generate the Ethernet and IP packet
	b = NewBuf();

	// Destination MAC address
	WriteBuf(b, p->MacHeader->SrcAddress, 6);
	WriteBuf(b, p->MacHeader->DestAddress, 6);
	WriteBuf(b, &p->MacHeader->Protocol, 2);

	if (p->TypeL3 == L3_IPV4)
	{
		// IPv4
		IPV4_HEADER v4;

		Zero(&v4, sizeof(v4));

		IPV4_SET_VERSION(&v4, 4);
		IPV4_SET_HEADER_LEN(&v4, 5);
		v4.TotalLength = Endian16((USHORT)(sizeof(IPV4_HEADER) + tcp_size));
		v4.Identification = Endian16(Rand16());
		IPV4_SET_FLAGS(&v4, 0x02);
		v4.TimeToLive = 128;
		v4.Protocol = IP_PROTO_TCP;
		v4.SrcIP = p->L3.IPv4Header->DstIP;
		v4.DstIP = p->L3.IPv4Header->SrcIP;
		v4.Checksum = IpChecksum(&v4, sizeof(v4));

		WriteBuf(b, &v4, sizeof(v4));
	}
	else
	{
		// IPv6
		IPV6_HEADER v6;

		Zero(&v6, sizeof(v6));

		IPV6_SET_VERSION(&v6, 6);
		v6.PayloadLength = Endian16(tcp_size);
		v6.NextHeader = IP_PROTO_TCP;
		v6.HopLimit = 64;

		Copy(&v6.SrcAddress, &p->IPv6HeaderPacketInfo.IPv6Header->DestAddress, sizeof(IPV6_ADDR));
		Copy(&v6.DestAddress, &p->IPv6HeaderPacketInfo.IPv6Header->SrcAddress, sizeof(IPV6_ADDR));

		WriteBuf(b, &v6, sizeof(v6));
	}

	WriteBuf(b, tcp_data, tcp_size);

	// Reply packet
	StorePacketToHubPa((HUB_PA *)src_session->PacketAdapter->Param,
		NULL, b->Buf, b->Size, NULL, false, false);

	// Release the memory
	Free(tcp_data);
	FreeBuf(payload);
	Free(b);
}