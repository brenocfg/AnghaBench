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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
#define  NETLINK_AUDIT 148 
#define  NETLINK_DNRTMSG 147 
#define  NETLINK_FIREWALL 146 
#define  NETLINK_INET_DIAG 145 
#define  NETLINK_IP6_FW 144 
#define  NETLINK_KOBJECT_UEVENT 143 
#define  NETLINK_NFLOG 142 
#define  NETLINK_ROUTE 141 
#define  NETLINK_SELINUX 140 
#define  NETLINK_XFRM 139 
#define  PF_APPLETALK 138 
#define  PF_INET 137 
#define  PF_INET6 136 
#define  PF_KEY 135 
#define  PF_NETLINK 134 
#define  PF_PACKET 133 
#define  PF_UNIX 132 
 int /*<<< orphan*/  SECCLASS_APPLETALK_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_DCCP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_KEY_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_AUDIT_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_DNRT_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_FIREWALL_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_IP6FW_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_KOBJECT_UEVENT_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_NFLOG_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_ROUTE_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_SELINUX_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_TCPDIAG_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_XFRM_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_PACKET_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_RAWIP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_TCP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_UDP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_UNIX_DGRAM_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_UNIX_STREAM_SOCKET ; 
#define  SOCK_DCCP 131 
#define  SOCK_DGRAM 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  default_protocol_dgram (int) ; 
 int /*<<< orphan*/  default_protocol_stream (int) ; 

__attribute__((used)) static inline u16 socket_type_to_security_class(int family, int type, int protocol)
{
	switch (family) {
	case PF_UNIX:
		switch (type) {
		case SOCK_STREAM:
		case SOCK_SEQPACKET:
			return SECCLASS_UNIX_STREAM_SOCKET;
		case SOCK_DGRAM:
			return SECCLASS_UNIX_DGRAM_SOCKET;
		}
		break;
	case PF_INET:
	case PF_INET6:
		switch (type) {
		case SOCK_STREAM:
			if (default_protocol_stream(protocol))
				return SECCLASS_TCP_SOCKET;
			else
				return SECCLASS_RAWIP_SOCKET;
		case SOCK_DGRAM:
			if (default_protocol_dgram(protocol))
				return SECCLASS_UDP_SOCKET;
			else
				return SECCLASS_RAWIP_SOCKET;
		case SOCK_DCCP:
			return SECCLASS_DCCP_SOCKET;
		default:
			return SECCLASS_RAWIP_SOCKET;
		}
		break;
	case PF_NETLINK:
		switch (protocol) {
		case NETLINK_ROUTE:
			return SECCLASS_NETLINK_ROUTE_SOCKET;
		case NETLINK_FIREWALL:
			return SECCLASS_NETLINK_FIREWALL_SOCKET;
		case NETLINK_INET_DIAG:
			return SECCLASS_NETLINK_TCPDIAG_SOCKET;
		case NETLINK_NFLOG:
			return SECCLASS_NETLINK_NFLOG_SOCKET;
		case NETLINK_XFRM:
			return SECCLASS_NETLINK_XFRM_SOCKET;
		case NETLINK_SELINUX:
			return SECCLASS_NETLINK_SELINUX_SOCKET;
		case NETLINK_AUDIT:
			return SECCLASS_NETLINK_AUDIT_SOCKET;
		case NETLINK_IP6_FW:
			return SECCLASS_NETLINK_IP6FW_SOCKET;
		case NETLINK_DNRTMSG:
			return SECCLASS_NETLINK_DNRT_SOCKET;
		case NETLINK_KOBJECT_UEVENT:
			return SECCLASS_NETLINK_KOBJECT_UEVENT_SOCKET;
		default:
			return SECCLASS_NETLINK_SOCKET;
		}
	case PF_PACKET:
		return SECCLASS_PACKET_SOCKET;
	case PF_KEY:
		return SECCLASS_KEY_SOCKET;
	case PF_APPLETALK:
		return SECCLASS_APPLETALK_SOCKET;
	}

	return SECCLASS_SOCKET;
}