#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ph ;
typedef  int /*<<< orphan*/  h ;
typedef  scalar_t__ USHORT ;
typedef  void* UINT ;
struct TYPE_15__ {int /*<<< orphan*/  Checksum; void* PacketLength; void* DstPort; void* SrcPort; void* PacketLength2; void* PacketLength1; int /*<<< orphan*/  Protocol; void* DstIP; void* SrcIP; } ;
typedef  TYPE_1__ UDP_HEADER ;
typedef  TYPE_1__ UDPV4_PSEUDO_HEADER ;
struct TYPE_16__ {int Size; TYPE_1__* Buf; } ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 void* Endian16 (scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  IP_PROTO_UDP ; 
 int /*<<< orphan*/  IpChecksum (TYPE_1__*,int) ; 
 TYPE_3__* NewBuf () ; 
 int /*<<< orphan*/  SeekBufToBegin (TYPE_3__*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

BUF *NnBuildUdpPacket(BUF *payload, UINT src_ip, USHORT src_port, UINT dst_ip, USHORT dst_port)
{
	BUF *ret = NewBuf();
	BUF *phbuf = NewBuf();
	UDPV4_PSEUDO_HEADER ph;
	UDP_HEADER h;

	// UDP pseudo header
	Zero(&ph, sizeof(ph));

	ph.SrcIP = src_ip;
	ph.DstIP = dst_ip;
	ph.SrcPort = Endian16(src_port);
	ph.DstPort = Endian16(dst_port);
	ph.Protocol = IP_PROTO_UDP;
	ph.PacketLength1 = ph.PacketLength2 = Endian16(payload->Size + (USHORT)sizeof(UDP_HEADER));

	WriteBuf(phbuf, &ph, sizeof(ph));
	WriteBufBuf(phbuf, payload);

	// UDP header
	Zero(&h, sizeof(h));
	h.SrcPort = Endian16(src_port);
	h.DstPort = Endian16(dst_port);
	h.PacketLength = Endian16(payload->Size + (USHORT)sizeof(UDP_HEADER));
	h.Checksum = IpChecksum(phbuf->Buf, phbuf->Size);

	WriteBuf(ret, &h, sizeof(h));
	WriteBuf(ret, payload->Buf, payload->Size);

	SeekBufToBegin(ret);

	FreeBuf(payload);
	FreeBuf(phbuf);

	return ret;
}