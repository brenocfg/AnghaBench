#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yes ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_9__ {int /*<<< orphan*/  ipv6_scope_id; } ;
struct TYPE_8__ {int IgnoreSendErr; int IsRawSocket; scalar_t__ Type; scalar_t__ socket; int UdpBroadcast; int /*<<< orphan*/  lock; int /*<<< orphan*/  SendNum; int /*<<< orphan*/  SendSize; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ ECONNREFUSED ; 
 scalar_t__ ECONNRESET ; 
 scalar_t__ EINTR ; 
 scalar_t__ EMSGSIZE ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ENOMEM ; 
 int GetIPAddrType6 (TYPE_2__*) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPToInAddr6 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int IPV6_ADDR_MULTICAST ; 
 int IsIP6 (TYPE_2__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int SOCK_LATER ; 
 scalar_t__ SOCK_UDP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ WSAEADDRNOTAVAIL ; 
 scalar_t__ WSAECONNRESET ; 
 scalar_t__ WSAEHOSTUNREACH ; 
 scalar_t__ WSAEINPROGRESS ; 
 scalar_t__ WSAEINVAL ; 
 scalar_t__ WSAEMSGSIZE ; 
 scalar_t__ WSAENETRESET ; 
 scalar_t__ WSAENETUNREACH ; 
 scalar_t__ WSAENOBUFS ; 
 scalar_t__ WSAEUSERS ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  Zero (struct sockaddr_in6*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int sendto (scalar_t__,void*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

UINT SendTo6Ex(SOCK *sock, IP *dest_addr, UINT dest_port, void *data, UINT size, bool broadcast)
{
	SOCKET s;
	int ret;
	struct sockaddr_in6 addr;
	UINT type;
	// Validate arguments
	if (sock != NULL)
	{
		sock->IgnoreSendErr = false;
	}
	if (sock == NULL || dest_addr == NULL || (sock->IsRawSocket == false && dest_port == 0) || data == NULL)
	{
		return 0;
	}
	if (dest_port >= 65536 && sock->IsRawSocket == false)
	{
		return 0;
	}
	if (sock->Type != SOCK_UDP || sock->socket == INVALID_SOCKET)
	{
		return 0;
	}
	if (size == 0)
	{
		return 0;
	}

	if (IsIP6(dest_addr) == false)
	{
		return 0;
	}

	s = sock->socket;
	Zero(&addr, sizeof(addr));
	addr.sin6_family = AF_INET6;
	if (sock->IsRawSocket == false)
	{
		addr.sin6_port = htons((USHORT)dest_port);
	}
	IPToInAddr6(&addr.sin6_addr, dest_addr);
	addr.sin6_scope_id = dest_addr->ipv6_scope_id;

	type = GetIPAddrType6(dest_addr);

	if ((type & IPV6_ADDR_MULTICAST) || broadcast)
	{
		if (sock->UdpBroadcast == false)
		{
			bool yes = true;

			sock->UdpBroadcast = true;

			(void)setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));
		}
	}

	ret = sendto(s, data, size, 0, (struct sockaddr *)&addr, sizeof(addr));
	if (ret != (int)size)
	{
		sock->IgnoreSendErr = false;

#ifdef	OS_WIN32
		if (WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAENETRESET || WSAGetLastError() == WSAEMSGSIZE || WSAGetLastError() == WSAENETUNREACH ||
			WSAGetLastError() == WSAENOBUFS || WSAGetLastError() == WSAEHOSTUNREACH || WSAGetLastError() == WSAEUSERS || WSAGetLastError() == WSAEINVAL || WSAGetLastError() == WSAEADDRNOTAVAIL)
		{
			sock->IgnoreSendErr = true;
		}
		else if (WSAGetLastError() == WSAEWOULDBLOCK || WSAGetLastError() == WSAEINPROGRESS)
		{
			return SOCK_LATER;
		}
		else
		{
			UINT e = WSAGetLastError();
		}
#else	// OS_WIN32
		if (errno == ECONNREFUSED || errno == ECONNRESET || errno == EMSGSIZE || errno == ENOBUFS || errno == ENOMEM || errno == EINTR)
		{
			sock->IgnoreSendErr = true;
		}
		else if (errno == EAGAIN)
		{
			return SOCK_LATER;
		}
#endif	// OS_WIN32
		return 0;
	}

	Lock(sock->lock);
	{
		sock->SendSize += (UINT64)size;
		sock->SendNum++;
	}
	Unlock(sock->lock);

	return ret;
}