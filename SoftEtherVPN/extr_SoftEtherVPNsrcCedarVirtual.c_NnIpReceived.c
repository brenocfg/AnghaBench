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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {scalar_t__ PublicIP; } ;
typedef  TYPE_1__ NATIVE_NAT ;

/* Variables and functions */
#define  IP_PROTO_ICMPV4 130 
#define  IP_PROTO_TCP 129 
#define  IP_PROTO_UDP 128 
 int /*<<< orphan*/  NnIcmpReceived (TYPE_1__*,scalar_t__,scalar_t__,void*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NnTcpReceived (TYPE_1__*,scalar_t__,scalar_t__,void*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NnUdpReceived (TYPE_1__*,scalar_t__,scalar_t__,void*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void NnIpReceived(NATIVE_NAT *t, UINT src_ip, UINT dest_ip, UINT protocol, void *data, UINT size,
				  UCHAR ttl, UCHAR *ip_header, UINT ip_header_size, UINT max_l3_size)
{
	// Validate arguments
	if (t == NULL || data == NULL)
	{
		return;
	}

	if (dest_ip != t->PublicIP)
	{
		// Destination IP is not a unicast
		return;
	}

	switch (protocol)
	{
	case IP_PROTO_UDP:
		// UDP
		NnUdpReceived(t, src_ip, dest_ip, data, size, ttl, max_l3_size);
		break;

	case IP_PROTO_TCP:
		// TCP
		NnTcpReceived(t, src_ip, dest_ip, data, size, ttl, max_l3_size);
		break;

	case IP_PROTO_ICMPV4:
		// ICMP
		NnIcmpReceived(t, src_ip, dest_ip, data, size, ttl, max_l3_size);
		break;
	}
}