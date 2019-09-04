#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
typedef  scalar_t__ USHORT ;
typedef  void* UINT ;
typedef  void* UCHAR ;
struct TYPE_17__ {scalar_t__ Size; } ;
struct TYPE_16__ {int /*<<< orphan*/  Checksum; void* DstIP; void* SrcIP; void* Protocol; void* TimeToLive; int /*<<< orphan*/  Identification; int /*<<< orphan*/  TotalLength; } ;
typedef  TYPE_1__ IPV4_HEADER ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Endian16 (scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  IPV4_SET_HEADER_LEN (TYPE_1__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_VERSION (TYPE_1__*,int) ; 
 int /*<<< orphan*/  IpChecksum (TYPE_1__*,int) ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/  Rand16 () ; 
 int /*<<< orphan*/  SeekBufToBegin (TYPE_2__*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

BUF *NnBuildIpPacket(BUF *payload, UINT src_ip, UINT dst_ip, UCHAR protocol, UCHAR ttl)
{
	BUF *ret = NewBuf();
	IPV4_HEADER h;

	if (ttl == 0)
	{
		ttl = 127;
	}

	// IP header
	Zero(&h, sizeof(h));
	IPV4_SET_VERSION(&h, 4);
	IPV4_SET_HEADER_LEN(&h, sizeof(IPV4_HEADER) / 4);
	h.TotalLength = Endian16((USHORT)sizeof(IPV4_HEADER) + payload->Size);
	h.Identification = Rand16();
	h.TimeToLive = ttl;
	h.Protocol = protocol;
	h.SrcIP = src_ip;
	h.DstIP = dst_ip;

	h.Checksum = IpChecksum(&h, sizeof(h));

	WriteBuf(ret, &h, sizeof(h));
	WriteBufBuf(ret, payload);

	SeekBufToBegin(ret);

	FreeBuf(payload);

	return ret;
}