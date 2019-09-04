#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int CancelAccept; int Disconnecting; int ServerMode; int IsReverseAcceptedSocket; int /*<<< orphan*/  ReverseAcceptEvent; int /*<<< orphan*/  ReverseAcceptQueue; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

void InjectNewReverseSocketToAccept(SOCK *listen_sock, SOCK *s, IP *client_ip, UINT client_port)
{
	bool ok = false;
	// Validate arguments
	if (listen_sock == NULL || s == NULL)
	{
		return;
	}

	LockQueue(listen_sock->ReverseAcceptQueue);
	{
		if (listen_sock->CancelAccept == false && listen_sock->Disconnecting == false)
		{
			InsertQueue(listen_sock->ReverseAcceptQueue, s);

			ok = true;

			s->ServerMode = true;
			s->IsReverseAcceptedSocket = true;

			Copy(&s->RemoteIP, client_ip, sizeof(IP));
			s->RemotePort = client_port;
		}
	}
	UnlockQueue(listen_sock->ReverseAcceptQueue);

	if (ok == false)
	{
		Disconnect(s);
		ReleaseSock(s);
	}
	else
	{
		Set(listen_sock->ReverseAcceptEvent);
	}
}