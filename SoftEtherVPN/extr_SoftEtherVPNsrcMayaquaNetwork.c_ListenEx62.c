#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_port; } ;
struct sockaddr {int dummy; } ;
struct in6_addr {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_port; } ;
typedef  int /*<<< orphan*/  in ;
typedef  int /*<<< orphan*/  addr ;
typedef  int UINT ;
struct TYPE_4__ {int Connected; int AsyncMode; int ServerMode; int ListenMode; int SecureMode; int LocalPort; int IPv6; int LocalOnly; int EnableConditionalAccept; scalar_t__ socket; int /*<<< orphan*/  Type; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  GetLocalHostIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPToInAddr6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* NewSock () ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOCK_TCP ; 
 int SOMAXCONN ; 
 int /*<<< orphan*/  Zero (struct sockaddr_in6*,int) ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ listen (scalar_t__,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SOCK *ListenEx62(UINT port, bool local_only, bool enable_ca)
{
	SOCKET s;
	SOCK *sock;
	struct sockaddr_in6 addr;
	struct in6_addr in;
	bool true_flag = true;
	IP localhost;
	UINT backlog = SOMAXCONN;
	// Validate arguments
	if (port == 0 || port >= 65536)
	{
		return NULL;
	}

#ifdef	OS_WIN32
	if (MsIsVista() == false)
	{
		// Disable the Conditional Accept due to a bug in Windows
		enable_ca = false;
	}
#endif	// OS_WIN32

	// Initialization
	Zero(&addr, sizeof(addr));
	Zero(&in, sizeof(in));
	GetLocalHostIP6(&localhost);

	addr.sin6_port = htons((UINT)port);
	addr.sin6_family = AF_INET6;

	if (local_only)
	{
		IPToInAddr6(&addr.sin6_addr, &localhost);

		enable_ca = false;
	}

	// Creating a socket
	s = socket(AF_INET6, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		return NULL;
	}

#ifdef	OS_UNIX
	// It is necessary to set the IPv6 Only flag on a UNIX system
	(void)setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &true_flag, sizeof(true_flag));
#endif	// OS_UNIX

#ifdef	OS_UNIX
	// This only have enabled for UNIX system since there is a bug
	// in the implementation of REUSEADDR in Windows OS
	(void)setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&true_flag, sizeof(bool));
#endif	// OS_UNIX

	if (bind(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in6)) != 0)
	{
		// Bind failure
		closesocket(s);
		return NULL;
	}

#ifdef	OS_WIN32
	if (enable_ca)
	{
		if (MsIsWinXPOrGreater())
		{
			setsockopt(s, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char *)&true_flag, sizeof(bool));

			backlog = 1;
		}
	}
#endif	// OS_WIN32

	if (listen(s, backlog))
	{
		// Listen failure
		closesocket(s);
		return NULL;
	}

	// Success
	sock = NewSock();
	sock->Connected = false;
	sock->AsyncMode = false;
	sock->ServerMode = true;
	sock->Type = SOCK_TCP;
	sock->socket = s;
	sock->ListenMode = true;
	sock->SecureMode = false;
	sock->LocalPort = port;
	sock->IPv6 = true;
	sock->LocalOnly = local_only;
	sock->EnableConditionalAccept = enable_ca;

	return sock;
}