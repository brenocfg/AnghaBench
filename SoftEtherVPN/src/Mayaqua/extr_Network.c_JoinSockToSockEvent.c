#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Type; int /*<<< orphan*/ * BulkRecvTube; int /*<<< orphan*/ * RecvTube; } ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 scalar_t__ SOCK_INPROC ; 
 int /*<<< orphan*/  SetTubeSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnixJoinSockToSockEvent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Win32JoinSockToSockEvent (TYPE_1__*,int /*<<< orphan*/ *) ; 

void JoinSockToSockEvent(SOCK *sock, SOCK_EVENT *event)
{
	// Validate arguments
	if (sock == NULL || event == NULL)
	{
		return;
	}

	if (sock->Type == SOCK_INPROC)
	{
		// Set the SockEvent on the receiver TUBE for in-process type socket
		SetTubeSockEvent(sock->RecvTube, event);
		return;
	}

	if (sock->BulkRecvTube != NULL)
	{
		// Set the SockEvent on the receiver TUBE in case of R-UDP socket
		SetTubeSockEvent(sock->BulkRecvTube, event);
	}

#ifdef	OS_WIN32
	Win32JoinSockToSockEvent(sock, event);
#else
	UnixJoinSockToSockEvent(sock, event);
#endif	// OS_WIN32
}