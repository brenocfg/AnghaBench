#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr6 ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  ipv6_scope_id; } ;
struct TYPE_5__ {scalar_t__ Type; int IsTtlSupported; int /*<<< orphan*/  lock; scalar_t__ CurrentTtl; scalar_t__ IPv6; int /*<<< orphan*/  socket; scalar_t__ UdpMaxMsgSize; int /*<<< orphan*/  RawSocketIPProtocol; scalar_t__ RemotePort; scalar_t__ LocalPort; scalar_t__ IsRawSocket; TYPE_3__ LocalIP; TYPE_3__ RemoteIP; } ;
typedef  TYPE_1__ SOCK ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 scalar_t__ IPV6_UNICAST_HOPS ; 
 scalar_t__ IP_TTL ; 
 int /*<<< orphan*/  InAddrToIP (TYPE_3__*,struct in_addr*) ; 
 int /*<<< orphan*/  InAddrToIP6 (TYPE_3__*,struct in6_addr*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ MAKE_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_TCP ; 
 scalar_t__ SOCK_UDP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 scalar_t__ SO_MAX_MSG_SIZE ; 
 scalar_t__ UDP_MAX_MSG_SIZE_DEFAULT ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

void QuerySocketInformation(SOCK *sock)
{
	// Validate arguments
	if (sock == NULL)
	{
		return;
	}

	Lock(sock->lock);
	{
		struct sockaddr_in6 sockaddr6;
		struct in6_addr *addr6;
		int size;
		DWORD dw;
		UINT opt_value = 0;

		if (sock->Type == SOCK_TCP)
		{
			// Get the information of the remote host
			size = sizeof(sockaddr6);
			if (getpeername(sock->socket, (struct sockaddr *)&sockaddr6, (int *)&size) == 0)
			{
				if (size >= sizeof(struct sockaddr_in6))
				{
					sock->RemotePort = (UINT)ntohs(sockaddr6.sin6_port);
					addr6 = &sockaddr6.sin6_addr;
					InAddrToIP6(&sock->RemoteIP, addr6);
					sock->RemoteIP.ipv6_scope_id = sockaddr6.sin6_scope_id;
				}
				else
				{
					struct sockaddr_in *sockaddr;
					struct in_addr *addr;

					sockaddr = (struct sockaddr_in *)&sockaddr6;
					sock->RemotePort = (UINT)ntohs(sockaddr->sin_port);
					addr = &sockaddr->sin_addr;
					InAddrToIP(&sock->RemoteIP, addr);
				}
			}
		}

		// Get the local host information
		size = sizeof(sockaddr6);
		if (getsockname(sock->socket, (struct sockaddr *)&sockaddr6, (int *)&size) == 0)
		{
			if (size >= sizeof(struct sockaddr_in6))
			{
				sock->LocalPort = (UINT)ntohs(sockaddr6.sin6_port);
				addr6 = &sockaddr6.sin6_addr;
				InAddrToIP6(&sock->LocalIP, addr6);
				sock->LocalIP.ipv6_scope_id = sockaddr6.sin6_scope_id;
			}
			else
			{
				struct sockaddr_in *sockaddr;
				struct in_addr *addr;

				sockaddr = (struct sockaddr_in *)&sockaddr6;
				sock->LocalPort = (UINT)ntohs(sockaddr->sin_port);
				addr = &sockaddr->sin_addr;
				InAddrToIP(&sock->LocalIP, addr);
			}
		}

		if (sock->IsRawSocket)
		{
			sock->LocalPort = sock->RemotePort = MAKE_SPECIAL_PORT(sock->RawSocketIPProtocol);
		}

		if (sock->Type == SOCK_UDP)
		{
			sock->UdpMaxMsgSize = UDP_MAX_MSG_SIZE_DEFAULT;

#ifdef	OS_WIN32
			if (true)
			{
				// Get the buffer size that can be transmitted and received at once
				UINT max_value = 0;
				int len = sizeof(UINT);

				if (getsockopt(sock->socket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&max_value, &len) == 0)
				{
					sock->UdpMaxMsgSize = max_value;
				}
			}
#endif	// OS_WIN32
		}

		if (sock->IPv6)
		{
#ifdef	IPV6_UNICAST_HOPS
			opt_value = IPV6_UNICAST_HOPS;
#endif	// IPV6_UNICAST_HOPS
		}
		else
		{
#ifdef	IP_TTL
			opt_value = IP_TTL;
#endif	// IP_TTL
		}

		// Support of the TTL value
		size = sizeof(DWORD);
		if (opt_value == 0 ||
			getsockopt(sock->socket, (sock->IPv6 ? IPPROTO_IPV6 : IPPROTO_IP), opt_value, (char *)&dw, &size) != 0)
		{
			sock->IsTtlSupported = false;
		}
		else
		{
			sock->IsTtlSupported = true;
			sock->CurrentTtl = dw;
		}
	}
	Unlock(sock->lock);
}