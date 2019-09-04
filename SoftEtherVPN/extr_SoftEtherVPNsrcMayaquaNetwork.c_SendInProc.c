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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {scalar_t__ Type; int Connected; int /*<<< orphan*/  SendTube; scalar_t__ Disconnecting; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 int IsTubeConnected (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_INPROC ; 
 int TubeSend (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

UINT SendInProc(SOCK *sock, void *data, UINT size)
{
	if (sock == NULL || sock->Type != SOCK_INPROC || sock->Disconnecting || sock->Connected == false)
	{
		return 0;
	}

	if (IsTubeConnected(sock->SendTube) == false)
	{
		return 0;
	}

	if (TubeSend(sock->SendTube, data, size, NULL) == false)
	{
		return 0;
	}

	return size;
}