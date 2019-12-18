#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {scalar_t__ Protocol; TYPE_3__* Tcp; } ;
struct TYPE_11__ {int /*<<< orphan*/  TcpSockList; } ;
struct TYPE_10__ {TYPE_1__* Sock; } ;
struct TYPE_9__ {int /*<<< orphan*/  SendSize; } ;
typedef  TYPE_2__ TCPSOCK ;
typedef  TYPE_3__ TCP ;
typedef  TYPE_4__ CONNECTION ;

/* Variables and functions */
 scalar_t__ CONNECTION_TCP ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_2__**) ; 
 int /*<<< orphan*/  FreeTcpSock (TYPE_2__*) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_2__** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void DisconnectTcpSockets(CONNECTION *c)
{
	UINT i, num;
	TCP *tcp;
	TCPSOCK **tcpsocks;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}
	if (c->Protocol != CONNECTION_TCP)
	{
		return;
	}

	tcp = c->Tcp;
	LockList(tcp->TcpSockList);
	{
		tcpsocks = ToArray(tcp->TcpSockList);
		num = LIST_NUM(tcp->TcpSockList);
		DeleteAll(tcp->TcpSockList);
	}
	UnlockList(tcp->TcpSockList);

	if (num != 0)
	{
		Debug("--- SOCKET STATUS ---\n");
		for (i = 0;i < num;i++)
		{
			TCPSOCK *ts = tcpsocks[i];
			Debug(" SOCK %2u: %u\n", i, ts->Sock->SendSize);
			FreeTcpSock(ts);
		}
	}

	Free(tcpsocks);
}