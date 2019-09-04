#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ip_header ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  UINT ;
typedef  void* UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  PayloadSize; void* Payload; void* Protocol; struct TYPE_6__* IPv6Header; int /*<<< orphan*/  DestAddress; int /*<<< orphan*/  SrcAddress; void* HopLimit; } ;
typedef  TYPE_1__ IPV6_HEADER_PACKET_INFO ;
typedef  TYPE_1__ IPV6_HEADER ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildIPv6PacketHeader (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPV6_SET_VERSION (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

BUF *BuildIPv6(IPV6_ADDR *dest_ip, IPV6_ADDR *src_ip, UINT id, UCHAR protocol, UCHAR hop_limit, void *data,
			   UINT size)
{
	IPV6_HEADER_PACKET_INFO info;
	IPV6_HEADER ip_header;
	BUF *buf;
	UINT size_for_headers;
	// Validate arguments
	if (dest_ip == NULL || src_ip == NULL || data == NULL)
	{
		return NULL;
	}
	if (hop_limit == 0)
	{
		hop_limit = 255;
	}

	// IPv6 header
	Zero(&ip_header, sizeof(ip_header));
	IPV6_SET_VERSION(&ip_header, 6);
	ip_header.HopLimit = hop_limit;
	Copy(&ip_header.SrcAddress, src_ip, sizeof(IPV6_ADDR));
	Copy(&ip_header.DestAddress, dest_ip, sizeof(IPV6_ADDR));

	// Arrangement of the packet header information
	Zero(&info, sizeof(info));
	info.IPv6Header = &ip_header;
	info.Protocol = protocol;
	info.Payload = data;
	info.PayloadSize = size;

	buf = BuildIPv6PacketHeader(&info, &size_for_headers);
	if (buf == NULL)
	{
		return NULL;
	}

	return buf;
}