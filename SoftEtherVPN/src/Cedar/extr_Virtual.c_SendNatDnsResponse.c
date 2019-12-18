#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ HostIP; } ;
typedef  TYPE_1__ VH ;
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_19__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_18__ {int Flag1; int Flag2; scalar_t__ AdditionalRRs; scalar_t__ AuthorityRRs; void* AnswerRRs; void* NumQuery; void* TransactionId; } ;
struct TYPE_17__ {int DnsGetIpFromHost; int DnsOk; scalar_t__ DestIp; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  SrcIp; scalar_t__ DnsTransactionId; int /*<<< orphan*/  DnsResponseHostName; int /*<<< orphan*/  DnsResponseIp; int /*<<< orphan*/  DnsTargetHostName; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  TYPE_3__ DNSV4_HEADER ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BuildDnsQueryPacket (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BuildDnsResponsePacketA (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BuildDnsResponsePacketPtr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 void* Endian16 (int) ; 
 scalar_t__ Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 TYPE_4__* NewBuf () ; 
 int /*<<< orphan*/  SPECIAL_IPV4_ADDR_LLMNR_DEST ; 
 int /*<<< orphan*/  SPECIAL_UDP_PORT_LLMNR ; 
 int /*<<< orphan*/  SendUdp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 TYPE_3__* ZeroMalloc (scalar_t__) ; 

void SendNatDnsResponse(VH *v, NAT_ENTRY *n)
{
	BUF *b;
	UINT dns_header_size;
	DNSV4_HEADER *dns;
	UINT src_ip;
	// Validate arguments
	if (n == NULL || v == NULL)
	{
		return;
	}

	// Generate the data
	b = NewBuf();

	// Add a Query
	if (n->DnsGetIpFromHost == false)
	{
		BuildDnsQueryPacket(b, n->DnsTargetHostName, false);
	}
	else
	{
		BuildDnsQueryPacket(b, n->DnsTargetHostName, true);
	}

	// Add a Response
	if (n->DnsOk)
	{
		if (n->DnsGetIpFromHost == false)
		{
			BuildDnsResponsePacketA(b, &n->DnsResponseIp);
		}
		else
		{
			BuildDnsResponsePacketPtr(b, n->DnsResponseHostName);
		}
	}

	// Generate a DNS header
	dns_header_size = sizeof(DNSV4_HEADER) + b->Size;

	dns = ZeroMalloc(dns_header_size);
	dns->TransactionId = Endian16((USHORT)n->DnsTransactionId);

	// Generate a response flag
	if (n->DnsOk)
	{
		dns->Flag1 = 0x85;
		dns->Flag2 = 0x80;
	}
	else
	{
		dns->Flag1 = 0x85;
		dns->Flag2 = 0x83;
	}

	dns->NumQuery = Endian16(1);
	dns->AnswerRRs = Endian16(n->DnsOk != false ? 1 : 0);
	dns->AuthorityRRs = 0;
	dns->AdditionalRRs = 0;

	// Settings, such as the source IP address
	src_ip = n->DestIp;
	if (src_ip == Endian32(SPECIAL_IPV4_ADDR_LLMNR_DEST) && n->DestPort == SPECIAL_UDP_PORT_LLMNR)
	{
		// Make a unicast response in the case of LLMNR packet
		src_ip = v->HostIP;

		dns->Flag1 = 0x84;
		dns->Flag2 = 0x00;
	}

	// Copy data
	Copy(((UCHAR *)dns) + sizeof(DNSV4_HEADER), b->Buf, b->Size);

	// Send this packet
	SendUdp(v, n->SrcIp, n->SrcPort, src_ip, n->DestPort, dns, dns_header_size);

	// Release the memory
	Free(dns);
	FreeBuf(b);
}