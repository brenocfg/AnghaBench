#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ Type; scalar_t__ TimeOut; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 scalar_t__ INFINITE ; 
 scalar_t__ SOCK_INPROC ; 
 scalar_t__ SOCK_UDP ; 
 scalar_t__ TIMEOUT_INFINITE ; 

void SetTimeout(SOCK *sock, UINT timeout)
{
	// Validate arguments
	if (sock == NULL)
	{
		return;
	}
	if (sock->Type == SOCK_UDP)
	{
		return;
	}

	if (timeout == INFINITE)
	{
		timeout = TIMEOUT_INFINITE;
	}

	sock->TimeOut = timeout;

//	Debug("SetTimeout(%u)\n",timeout);

	if (sock->Type != SOCK_INPROC)
	{
#ifdef OS_WIN32
		setsockopt(sock->socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(UINT));
		setsockopt(sock->socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(UINT));
#endif

#ifdef OS_UNIX
#ifndef UNIX_SOLARIS
		{
			struct timeval tv_timeout;

			tv_timeout.tv_sec = timeout / 1000; // miliseconds to seconds
			tv_timeout.tv_usec = (timeout % 1000) * 1000; // miliseconds to microseconds

			(void)setsockopt(sock->socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv_timeout, sizeof(tv_timeout));
			(void)setsockopt(sock->socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv_timeout, sizeof(tv_timeout));
		}
#endif // UNIX_SOLARIS
#endif // OS_UNIX
	}
}