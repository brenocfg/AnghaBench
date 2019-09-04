#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UINT ;
struct TYPE_14__ {void* NextHeader; } ;
struct TYPE_13__ {int Size; scalar_t__ Buf; } ;
struct TYPE_12__ {int /*<<< orphan*/  PayloadLength; } ;
struct TYPE_11__ {int PayloadSize; TYPE_5__* Payload; int /*<<< orphan*/  Protocol; TYPE_5__* FragmentHeader; int /*<<< orphan*/  RoutingHeaderSize; int /*<<< orphan*/ * RoutingHeader; int /*<<< orphan*/  EndPointHeaderSize; int /*<<< orphan*/ * EndPointHeader; int /*<<< orphan*/  HopHeaderSize; int /*<<< orphan*/ * HopHeader; TYPE_5__* IPv6Header; } ;
typedef  int /*<<< orphan*/  QUEUE ;
typedef  TYPE_1__ IPV6_HEADER_PACKET_INFO ;
typedef  TYPE_2__ IPV6_HEADER ;
typedef  int /*<<< orphan*/  IPV6_FRAGMENT_HEADER ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BuildAndAddIPv6PacketOptionHeader (TYPE_3__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Endian16 (int) ; 
 int /*<<< orphan*/  IPV6_HEADER_ENDPOINT ; 
 int /*<<< orphan*/  IPV6_HEADER_FRAGMENT ; 
 int /*<<< orphan*/  IPV6_HEADER_HOP ; 
 int /*<<< orphan*/  IPV6_HEADER_NONE ; 
 int /*<<< orphan*/  IPV6_HEADER_ROUTING ; 
 void* IPv6GetNextHeaderFromQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertQueueInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* NewBuf () ; 
 int /*<<< orphan*/ * NewQueueFast () ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,TYPE_5__*,int) ; 

BUF *BuildIPv6PacketHeader(IPV6_HEADER_PACKET_INFO *info, UINT *bytes_before_payload)
{
	BUF *b;
	QUEUE *q;
	UINT bbp = 0;
	// Validate arguments
	if (info == NULL)
	{
		return NULL;
	}

	b = NewBuf();
	q = NewQueueFast();

	// Create the list of options headers
	if (info->HopHeader != NULL)
	{
		InsertQueueInt(q, IPV6_HEADER_HOP);
	}
	if (info->EndPointHeader != NULL)
	{
		InsertQueueInt(q, IPV6_HEADER_ENDPOINT);
	}
	if (info->RoutingHeader != NULL)
	{
		InsertQueueInt(q, IPV6_HEADER_ROUTING);
	}
	if (info->FragmentHeader != NULL)
	{
		InsertQueueInt(q, IPV6_HEADER_FRAGMENT);
	}
	InsertQueueInt(q, info->Protocol);

	// IPv6 header
	info->IPv6Header->NextHeader = IPv6GetNextHeaderFromQueue(q);
	WriteBuf(b, info->IPv6Header, sizeof(IPV6_HEADER));

	// Hop-by-hop option header
	if (info->HopHeader != NULL)
	{
		BuildAndAddIPv6PacketOptionHeader(b, info->HopHeader,
			IPv6GetNextHeaderFromQueue(q), info->HopHeaderSize);
	}

	// End point option header
	if (info->EndPointHeader != NULL)
	{
		BuildAndAddIPv6PacketOptionHeader(b, info->EndPointHeader,
			IPv6GetNextHeaderFromQueue(q), info->EndPointHeaderSize);
	}

	// Routing header
	if (info->RoutingHeader != NULL)
	{
		BuildAndAddIPv6PacketOptionHeader(b, info->RoutingHeader,
			IPv6GetNextHeaderFromQueue(q), info->RoutingHeaderSize);
	}

	// Fragment header
	if (info->FragmentHeader != NULL)
	{
		info->FragmentHeader->NextHeader = IPv6GetNextHeaderFromQueue(q);
		WriteBuf(b, info->FragmentHeader, sizeof(IPV6_FRAGMENT_HEADER));
	}

	bbp = b->Size;
	if (info->FragmentHeader == NULL)
	{
		bbp += sizeof(IPV6_FRAGMENT_HEADER);
	}

	// Payload
	if (info->Protocol != IPV6_HEADER_NONE)
	{
		WriteBuf(b, info->Payload, info->PayloadSize);
	}

	ReleaseQueue(q);

	SeekBuf(b, 0, 0);

	// Payload length
	((IPV6_HEADER *)b->Buf)->PayloadLength = Endian16(b->Size - (USHORT)sizeof(IPV6_HEADER));

	if (bytes_before_payload != NULL)
	{
		// Calculate the length just before the payload
		// (by assuming fragment header is always included)
		*bytes_before_payload = bbp;
	}

	return b;
}