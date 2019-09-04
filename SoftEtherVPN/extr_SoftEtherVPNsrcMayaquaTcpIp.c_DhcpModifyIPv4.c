#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_18__ {scalar_t__ Checksum; } ;
typedef  TYPE_4__ UDP_HEADER ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_20__ {void* Buf; scalar_t__ Size; } ;
struct TYPE_17__ {TYPE_2__* IPv4Header; } ;
struct TYPE_15__ {TYPE_4__* UDPHeader; } ;
struct TYPE_19__ {scalar_t__ TypeL3; scalar_t__ TypeL4; scalar_t__ TypeL7; scalar_t__ PayloadSize; void* PacketData; scalar_t__ PacketSize; TYPE_3__ L3; TYPE_1__ L4; int /*<<< orphan*/  Payload; } ;
struct TYPE_16__ {int /*<<< orphan*/  DstIP; int /*<<< orphan*/  SrcIP; } ;
typedef  TYPE_5__ PKT ;
typedef  int /*<<< orphan*/  DHCP_MODIFY_OPTION ;
typedef  TYPE_6__ BUF ;

/* Variables and functions */
 scalar_t__ CalcChecksumForIPv4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_6__* DhcpModify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_6__*) ; 
 int /*<<< orphan*/  FreePacket (TYPE_5__*) ; 
 int /*<<< orphan*/  IP_PROTO_UDP ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L4_UDP ; 
 scalar_t__ L7_DHCPV4 ; 
 TYPE_6__* NewBuf () ; 
 TYPE_5__* ParsePacketEx4 (void*,scalar_t__,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_6__*,void*,scalar_t__) ; 

BUF *DhcpModifyIPv4(DHCP_MODIFY_OPTION *m, void *data, UINT size)
{
	PKT *p;
	BUF *ret = NULL;
	// Validate arguments
	if (m == NULL || data == NULL || size == 0)
	{
		return NULL;
	}

	p = ParsePacketEx4(data, size, false, 0, false, false, false);

	if (p != NULL && p->TypeL3 == L3_IPV4 && p->TypeL4 == L4_UDP && p->TypeL7 == L7_DHCPV4)
	{
		BUF *new_buf = DhcpModify(m, p->Payload, p->PayloadSize);

		if (new_buf != NULL)
		{
			ret = NewBuf();

			WriteBuf(ret, p->PacketData, p->PacketSize - p->PayloadSize);
			WriteBuf(ret, new_buf->Buf, new_buf->Size);

			FreeBuf(new_buf);
		}
	}

	FreePacket(p);

	if (ret != NULL)
	{
		PKT *p = ParsePacketEx4(ret->Buf, ret->Size, false, 0, false, false, false);

		if (p != NULL)
		{
			// Recalculation of the UDP checksum
			if (p->TypeL3 == L3_IPV4 && p->TypeL4 == L4_UDP)
			{
				UDP_HEADER *udp = p->L4.UDPHeader;

				udp->Checksum = 0;
				udp->Checksum = CalcChecksumForIPv4(p->L3.IPv4Header->SrcIP,
					p->L3.IPv4Header->DstIP,
					IP_PROTO_UDP,
					udp,
					p->PacketSize - (UINT)(((UCHAR *)udp) - ((UCHAR *)p->PacketData)), 0);
			}

			FreePacket(p);
		}
	}

	return ret;
}