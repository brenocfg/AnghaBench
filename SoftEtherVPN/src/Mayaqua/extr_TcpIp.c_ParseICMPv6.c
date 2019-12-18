#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  icmp_info ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_13__ {scalar_t__ HeaderPointer; int /*<<< orphan*/ * NeighborAdvertisementHeader; int /*<<< orphan*/ * NeighborSoliciationHeader; int /*<<< orphan*/ * RouterAdvertisementHeader; int /*<<< orphan*/ * RouterSoliciationHeader; } ;
struct TYPE_12__ {void* SeqNo; void* Identifier; } ;
struct TYPE_17__ {int Type; int DataSize; int EchoDataSize; TYPE_3__ Headers; int /*<<< orphan*/  OptionList; int /*<<< orphan*/ * Data; int /*<<< orphan*/ * EchoData; TYPE_2__ EchoHeader; int /*<<< orphan*/  Code; } ;
struct TYPE_16__ {int /*<<< orphan*/  SeqNo; int /*<<< orphan*/  Identifier; } ;
struct TYPE_15__ {int Type; int /*<<< orphan*/  Code; } ;
struct TYPE_11__ {TYPE_5__* ICMPHeader; } ;
struct TYPE_14__ {int /*<<< orphan*/  ICMPv6HeaderPacketInfo; int /*<<< orphan*/  TypeL4; TYPE_1__ L4; } ;
typedef  TYPE_4__ PKT ;
typedef  TYPE_5__ ICMP_HEADER ;
typedef  TYPE_6__ ICMP_ECHO ;
typedef  int /*<<< orphan*/  ICMPV6_ROUTER_SOLICIATION_HEADER ;
typedef  int /*<<< orphan*/  ICMPV6_ROUTER_ADVERTISEMENT_HEADER ;
typedef  int /*<<< orphan*/  ICMPV6_NEIGHBOR_SOLICIATION_HEADER ;
typedef  int /*<<< orphan*/  ICMPV6_NEIGHBOR_ADVERTISEMENT_HEADER ;
typedef  TYPE_7__ ICMPV6_HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 void* Endian16 (int /*<<< orphan*/ ) ; 
#define  ICMPV6_TYPE_ECHO_REQUEST 133 
#define  ICMPV6_TYPE_ECHO_RESPONSE 132 
#define  ICMPV6_TYPE_NEIGHBOR_ADVERTISEMENT 131 
#define  ICMPV6_TYPE_NEIGHBOR_SOLICIATION 130 
#define  ICMPV6_TYPE_ROUTER_ADVERTISEMENT 129 
#define  ICMPV6_TYPE_ROUTER_SOLICIATION 128 
 int /*<<< orphan*/  L4_ICMPV6 ; 
 int ParseICMPv6Options (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Zero (TYPE_7__*,int) ; 

bool ParseICMPv6(PKT *p, UCHAR *buf, UINT size)
{
	ICMPV6_HEADER_INFO icmp_info;
	ICMP_HEADER *icmp;
	ICMP_ECHO *echo;
	UINT msg_size;
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	Zero(&icmp_info, sizeof(icmp_info));

	if (size < sizeof(ICMP_HEADER))
	{
		return false;
	}

	icmp = (ICMP_HEADER *)buf;
	p->L4.ICMPHeader = icmp;

	msg_size = size - sizeof(ICMP_HEADER);

	icmp_info.Type = icmp->Type;
	icmp_info.Code = icmp->Code;
	icmp_info.Data = ((UCHAR *)buf) + sizeof(ICMP_HEADER);
	icmp_info.DataSize = msg_size;

	switch (icmp_info.Type)
	{
	case ICMPV6_TYPE_ECHO_REQUEST:
	case ICMPV6_TYPE_ECHO_RESPONSE:
		// ICMP Echo Request / Response
		if (icmp_info.DataSize < sizeof(ICMP_ECHO))
		{
			return false;
		}

		echo = (ICMP_ECHO *)icmp_info.Data;

		icmp_info.EchoHeader.Identifier = Endian16(echo->Identifier);
		icmp_info.EchoHeader.SeqNo = Endian16(echo->SeqNo);
		icmp_info.EchoData = (UCHAR *)echo + sizeof(ICMP_ECHO);
		icmp_info.EchoDataSize = icmp_info.DataSize - sizeof(ICMP_ECHO);

		break;

	case ICMPV6_TYPE_ROUTER_SOLICIATION:
		// Router Solicitation
		if (icmp_info.DataSize < sizeof(ICMPV6_ROUTER_SOLICIATION_HEADER))
		{
			return false;
		}

		icmp_info.Headers.RouterSoliciationHeader =
			(ICMPV6_ROUTER_SOLICIATION_HEADER *)(((UCHAR *)icmp_info.Data));

		if (ParseICMPv6Options(&icmp_info.OptionList, ((UCHAR *)icmp_info.Headers.HeaderPointer) + sizeof(ICMPV6_ROUTER_SOLICIATION_HEADER),
			icmp_info.DataSize - sizeof(ICMPV6_ROUTER_SOLICIATION_HEADER)) == false)
		{
			return false;
		}

		break;

	case ICMPV6_TYPE_ROUTER_ADVERTISEMENT:
		// Router Advertisement
		if (icmp_info.DataSize < sizeof(ICMPV6_ROUTER_ADVERTISEMENT_HEADER))
		{
			return false;
		}

		icmp_info.Headers.RouterAdvertisementHeader =
			(ICMPV6_ROUTER_ADVERTISEMENT_HEADER *)(((UCHAR *)icmp_info.Data));

		if (ParseICMPv6Options(&icmp_info.OptionList, ((UCHAR *)icmp_info.Headers.HeaderPointer) + sizeof(ICMPV6_ROUTER_ADVERTISEMENT_HEADER),
			icmp_info.DataSize - sizeof(ICMPV6_ROUTER_ADVERTISEMENT_HEADER)) == false)
		{
			return false;
		}

		break;

	case ICMPV6_TYPE_NEIGHBOR_SOLICIATION:
		// Neighbor Solicitation
		if (icmp_info.DataSize < sizeof(ICMPV6_NEIGHBOR_SOLICIATION_HEADER))
		{
			return false;
		}

		icmp_info.Headers.NeighborSoliciationHeader =
			(ICMPV6_NEIGHBOR_SOLICIATION_HEADER *)(((UCHAR *)icmp_info.Data));

		if (ParseICMPv6Options(&icmp_info.OptionList, ((UCHAR *)icmp_info.Headers.HeaderPointer) + sizeof(ICMPV6_NEIGHBOR_SOLICIATION_HEADER),
			icmp_info.DataSize - sizeof(ICMPV6_NEIGHBOR_SOLICIATION_HEADER)) == false)
		{
			return false;
		}

		break;

	case ICMPV6_TYPE_NEIGHBOR_ADVERTISEMENT:
		// Neighbor Advertisement
		if (icmp_info.DataSize < sizeof(ICMPV6_NEIGHBOR_ADVERTISEMENT_HEADER))
		{
			return false;
		}

		icmp_info.Headers.NeighborAdvertisementHeader =
			(ICMPV6_NEIGHBOR_ADVERTISEMENT_HEADER *)(((UCHAR *)icmp_info.Data));

		if (ParseICMPv6Options(&icmp_info.OptionList, ((UCHAR *)icmp_info.Headers.HeaderPointer) + sizeof(ICMPV6_NEIGHBOR_ADVERTISEMENT_HEADER),
			icmp_info.DataSize - sizeof(ICMPV6_NEIGHBOR_ADVERTISEMENT_HEADER)) == false)
		{
			return false;
		}

		break;
	}

	p->TypeL4 = L4_ICMPV6;
	Copy(&p->ICMPv6HeaderPacketInfo, &icmp_info, sizeof(ICMPV6_HEADER_INFO));

	return true;
}