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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ Type; int Connected; int ListenMode; scalar_t__ socket; int SecureMode; int WriteBlocked; scalar_t__ AsyncMode; int /*<<< orphan*/  lock; int /*<<< orphan*/  SendNum; int /*<<< orphan*/  SendSize; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SEND_BUF_MEM_SIZE ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int SOCKET_ERROR ; 
 scalar_t__ SOCK_INPROC ; 
 scalar_t__ SOCK_LATER ; 
 scalar_t__ SOCK_TCP ; 
 scalar_t__ SecureSend (TYPE_1__*,void*,scalar_t__) ; 
 scalar_t__ SendInProc (TYPE_1__*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ errno ; 
 int send (scalar_t__,void*,scalar_t__,int /*<<< orphan*/ ) ; 

UINT Send(SOCK *sock, void *data, UINT size, bool secure)
{
	SOCKET s;
	int ret;
	// Validate arguments
	if (sock == NULL || data == NULL || size == 0)
	{
		return 0;
	}
	if (sock->Type == SOCK_INPROC)
	{
		return SendInProc(sock, data, size);
	}
	size = MIN(size, MAX_SEND_BUF_MEM_SIZE);
	if (sock->Type != SOCK_TCP || sock->Connected == false || sock->ListenMode != false ||
		sock->socket == INVALID_SOCKET)
	{
		return 0;
	}
	if (secure != false && sock->SecureMode == false)
	{
		return 0;
	}

	if (secure)
	{
		return SecureSend(sock, data, size);
	}

	// Transmission
	s = sock->socket;
	ret = send(s, data, size, 0);
	if (ret > 0)
	{
		// Successful transmission
		Lock(sock->lock);
		{
			sock->SendSize += (UINT64)ret;
			sock->SendNum++;
		}
		Unlock(sock->lock);
		sock->WriteBlocked = false;
		return (UINT)ret;
	}

	// Transmission failure
	if (sock->AsyncMode)
	{
		// In asynchronous mode, examine the error
		if (ret == SOCKET_ERROR)
		{
#ifdef	OS_WIN32
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				// In blocking
				sock->WriteBlocked = true;
				return SOCK_LATER;
			}
			else
			{
				//Debug("Socket Error: %u\n", WSAGetLastError());
			}
#else	// OS_WIN32
			if (errno == EAGAIN)
			{
				// In blocking
				sock->WriteBlocked = true;
				return SOCK_LATER;
			}
#endif	// OS_WIN32
		}
	}

	// Disconnected
	Disconnect(sock);
	return 0;
}