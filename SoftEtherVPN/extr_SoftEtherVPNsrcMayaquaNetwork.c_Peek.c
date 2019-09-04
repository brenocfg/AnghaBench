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
typedef  int UINT ;
struct TYPE_3__ {scalar_t__ Type; int Connected; int ListenMode; scalar_t__ socket; scalar_t__ AsyncMode; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  MSG_PEEK ; 
 scalar_t__ SOCK_INPROC ; 
 scalar_t__ SOCK_TCP ; 
 int recv (scalar_t__,void*,int,int /*<<< orphan*/ ) ; 

UINT Peek(SOCK *sock, void *data, UINT size)
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
		return 0;
	}
	if (sock->Type != SOCK_TCP || sock->Connected == false || sock->ListenMode != false ||
		sock->socket == INVALID_SOCKET)
	{
		return 0;
	}
	if (sock->AsyncMode)
	{
		return 0;
	}

	// Receive
	s = sock->socket;

	ret = recv(s, data, size, MSG_PEEK);

	//Debug("Peek: %u\n", ret);

	if (ret > 0)
	{
		return ret;
	}

	return 0;
}