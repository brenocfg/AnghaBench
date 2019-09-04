#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_25__ {int Size; int OptionSize; TYPE_8__* Header; TYPE_11__* ParsedOptionList; int /*<<< orphan*/ * OptionData; int /*<<< orphan*/  OpCode; int /*<<< orphan*/ * OptionList; void* DestPort; void* SrcPort; int /*<<< orphan*/  DestIP; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/ * Data; } ;
struct TYPE_24__ {scalar_t__ ServerIP; int /*<<< orphan*/  YourIP; } ;
struct TYPE_23__ {int Size; scalar_t__ Data; } ;
struct TYPE_21__ {TYPE_4__* UDPHeader; } ;
struct TYPE_19__ {TYPE_2__* IPv4Header; } ;
struct TYPE_17__ {scalar_t__ PointerL7; } ;
struct TYPE_22__ {scalar_t__ TypeL3; scalar_t__ TypeL4; scalar_t__ TypeL7; int PacketSize; TYPE_5__ L4; TYPE_3__ L3; TYPE_1__ L7; scalar_t__ PacketData; } ;
struct TYPE_20__ {int /*<<< orphan*/  DstPort; int /*<<< orphan*/  SrcPort; } ;
struct TYPE_18__ {int /*<<< orphan*/  DstIP; int /*<<< orphan*/  SrcIP; } ;
struct TYPE_16__ {scalar_t__ ServerAddress; int /*<<< orphan*/  ClientAddress; } ;
typedef  TYPE_6__ PKT ;
typedef  TYPE_7__ DHCP_OPTION ;
typedef  TYPE_8__ DHCPV4_HEADER ;
typedef  TYPE_9__ DHCPV4_DATA ;

/* Variables and functions */
 int /*<<< orphan*/ * Clone (scalar_t__,int) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  DHCP_ID_MESSAGE_TYPE ; 
 int /*<<< orphan*/  DHCP_MAGIC_COOKIE ; 
 void* Endian16 (int /*<<< orphan*/ ) ; 
 int Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeDHCPv4Data (TYPE_9__*) ; 
 TYPE_7__* GetDhcpOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L4_UDP ; 
 scalar_t__ L7_DHCPV4 ; 
 TYPE_11__* ParseDhcpOptionList (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ParseDhcpOptions (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_9__* ZeroMalloc (int) ; 

DHCPV4_DATA *ParseDHCPv4Data(PKT *pkt)
{
	DHCPV4_DATA *d;
	UCHAR *data;
	UINT size;
	UINT magic_cookie = Endian32(DHCP_MAGIC_COOKIE);
	bool ok = false;
	DHCP_OPTION *o;
	// Validate arguments
	if (pkt == NULL)
	{
		return NULL;
	}
	if (pkt->TypeL3 != L3_IPV4 || pkt->TypeL4 != L4_UDP || pkt->TypeL7 != L7_DHCPV4)
	{
		return NULL;
	}

	d = ZeroMalloc(sizeof(DHCPV4_DATA));
	d->Size = (UINT)(pkt->PacketSize - (((UCHAR *)pkt->L7.PointerL7) - ((UCHAR *)pkt->PacketData)));
	d->Data = Clone(pkt->L7.PointerL7, d->Size);

	if (d->Size < sizeof(DHCPV4_HEADER))
	{
		goto LABEL_ERROR;
	}

	// Header
	d->Header = (DHCPV4_HEADER *)d->Data;

	data = d->Data;
	size = d->Size;

	// Search for the Magic Cookie
	ok = false;
	while (size >= 5)
	{
		if (Cmp(data, &magic_cookie, 4) == 0)
		{
			// Found
			data += 4;
			size -= 4;
			ok = true;
			break;
		}

		data++;
		size--;
	}

	if (ok == false)
	{
		// Magic Cookie not found
		goto LABEL_ERROR;
	}

	// Parse the DHCP Options
	d->OptionData = data;
	d->OptionSize = size;

	d->OptionList = ParseDhcpOptions(data, size);
	if (d->OptionList == NULL)
	{
		// Parsing failure
		goto LABEL_ERROR;
	}

	UINTToIP(&d->SrcIP, pkt->L3.IPv4Header->SrcIP);
	UINTToIP(&d->DestIP, pkt->L3.IPv4Header->DstIP);

	d->SrcPort = Endian16(pkt->L4.UDPHeader->SrcPort);
	d->DestPort = Endian16(pkt->L4.UDPHeader->DstPort);

	o = GetDhcpOption(d->OptionList, DHCP_ID_MESSAGE_TYPE);
	if (o == NULL || o->Size != 1)
	{
		goto LABEL_ERROR;
	}

	d->OpCode = *((UCHAR *)o->Data);

	d->ParsedOptionList = ParseDhcpOptionList(d->OptionData, d->OptionSize);

	if (d->ParsedOptionList == NULL)
	{
		goto LABEL_ERROR;
	}

	if (d->ParsedOptionList->ServerAddress == 0)
	{
		d->ParsedOptionList->ServerAddress = d->Header->ServerIP;
	}

	d->ParsedOptionList->ClientAddress = d->Header->YourIP;

	return d;

LABEL_ERROR:
	FreeDHCPv4Data(d);
	return NULL;
}