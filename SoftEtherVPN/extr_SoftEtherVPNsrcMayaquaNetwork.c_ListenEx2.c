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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
typedef  int /*<<< orphan*/  in ;
typedef  int /*<<< orphan*/  addr ;
typedef  int UINT ;
struct TYPE_4__ {int Connected; int AsyncMode; int ServerMode; int ListenMode; int SecureMode; int LocalPort; int LocalOnly; int EnableConditionalAccept; scalar_t__ socket; int /*<<< orphan*/  Type; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPToInAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* NewSock () ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOCK_TCP ; 
 int SOMAXCONN ; 
 int /*<<< orphan*/  SetIP (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (struct sockaddr_in*,int) ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ listen (scalar_t__,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SOCK *ListenEx2(UINT port, bool local_only, bool enable_ca, IP *listen_ip)
{
	SOCKET s;
	SOCK *sock;
	struct sockaddr_in addr;
	struct in_addr in;
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
	SetIP(&localhost, 127, 0, 0, 1);

	addr.sin_port = htons((UINT)port);
	if (listen_ip == NULL)
	{
		*((UINT *)&addr.sin_addr) = htonl(INADDR_ANY);
	}
	else
	{
		IPToInAddr(&addr.sin_addr, listen_ip);
	}
	addr.sin_family = AF_INET;

	if (local_only)
	{
		IPToInAddr(&addr.sin_addr, &localhost);

		enable_ca = false;
	}

	// Creating a socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		return NULL;
	}

#ifdef	OS_UNIX
	// This only have enabled for UNIX system since there is a bug
	// in the implementation of REUSEADDR in Windows OS
	(void)setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&true_flag, sizeof(bool));
#endif	// OS_UNIX

	if (bind(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0)
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
	sock->LocalOnly = local_only;
	sock->EnableConditionalAccept = enable_ca;

	return sock;
}