#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  c ;
typedef  int UINT ;
struct TYPE_14__ {TYPE_1__* ListenSocket; } ;
struct TYPE_13__ {int LocalPort; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ CHECK_NETWORK_1 ;

/* Variables and functions */
 int /*<<< orphan*/  CheckNetworkListenThread ; 
 TYPE_1__* Connect (char*,int) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__**) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Print (char*,int) ; 
 int Recv (TYPE_1__*,int*,int,int) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int SOCK_LATER ; 
 int StartSSL (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__** ZeroMalloc (int) ; 

bool CheckNetwork()
{
	CHECK_NETWORK_1 c;
	THREAD *t;
	SOCK *listen_socket;
	UINT port;
	UINT i, num;
	bool ok = true;
	SOCK **socks;
	SOCK_EVENT *se = NewSockEvent();

	Zero(&c, sizeof(c));
	t = NewThread(CheckNetworkListenThread, &c);
	WaitThreadInit(t);

	listen_socket = c.ListenSocket;

	port = listen_socket->LocalPort;

	num = 8;
	socks = ZeroMalloc(sizeof(SOCK *) * num);
	for (i = 0;i < num;i++)
	{
		socks[i] = Connect("localhost", port);
		if (socks[i] == NULL)
		{
			Print("Connect Failed. (%u)\n", i);
			ok = false;
			num = i;
			break;
		}
		if (StartSSL(socks[i], NULL, NULL) == false)
		{
			ReleaseSock(socks[i]);
			Print("Connect Failed. (%u)\n", i);
			ok = false;
			num = i;
			break;
		}

		JoinSockToSockEvent(socks[i], se);
	}

	if (ok)
	{
		while (true)
		{
			UINT i;
			bool end = false;
			bool all_blocked = true;

			for (i = 0;i < num;i++)
			{
				UINT n;
				UINT ret;

				n = 0;
				ret = Recv(socks[i], &n, sizeof(UINT), true);
				if (ret == 0)
				{
					Print("Recv Failed (Disconnected).\n", ret);
					end = true;
					ok = false;
				}
				if (ret != SOCK_LATER)
				{
					all_blocked = false;
				}

				if (n >= 128)
				{
					end = true;
				}
			}

			if (end)
			{
				break;
			}

			if (all_blocked)
			{
				WaitSockEvent(se, INFINITE);
			}
		}
	}

	for (i = 0;i < num;i++)
	{
		Disconnect(socks[i]);
		ReleaseSock(socks[i]);
	}
	Free(socks);

	Disconnect(listen_socket);

	WaitThread(t, INFINITE);
	ReleaseThread(t);

	ReleaseSock(listen_socket);

	ReleaseSockEvent(se);

	return ok;
}