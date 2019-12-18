#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VH ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
#define  IP_PROTO_ICMPV4 130 
#define  IP_PROTO_TCP 129 
#define  IP_PROTO_UDP 128 
 int /*<<< orphan*/  VirtualIcmpReceived (int /*<<< orphan*/ *,int,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  VirtualTcpReceived (int /*<<< orphan*/ *,int,int,void*,int,int) ; 
 int /*<<< orphan*/  VirtualUdpReceived (int /*<<< orphan*/ *,int,int,void*,int,int,int,int) ; 

void IpReceived(VH *v, UINT src_ip, UINT dest_ip, UINT protocol, void *data, UINT size, bool mac_broadcast, UCHAR ttl, UCHAR *ip_header, UINT ip_header_size, bool is_local_mac, UINT max_l3_size)
{
	// Validate arguments
	if (v == NULL || data == NULL)
	{
		return;
	}

	// Deliver the data to the supported high-level protocol
	switch (protocol)
	{
	case IP_PROTO_ICMPV4:	// ICMPv4
		if (mac_broadcast == false)
		{
			VirtualIcmpReceived(v, src_ip, dest_ip, data, size, ttl, ip_header, ip_header_size, max_l3_size);
		}
		break;

	case IP_PROTO_TCP:		// TCP
		if (mac_broadcast == false)
		{
			VirtualTcpReceived(v, src_ip, dest_ip, data, size, max_l3_size);
		}
		break;

	case IP_PROTO_UDP:		// UDP
		VirtualUdpReceived(v, src_ip, dest_ip, data, size, mac_broadcast, is_local_mac, max_l3_size);
		break;
	}
}