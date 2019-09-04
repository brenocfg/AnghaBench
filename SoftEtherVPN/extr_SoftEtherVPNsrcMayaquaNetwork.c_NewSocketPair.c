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
typedef  void* UINT ;
struct TYPE_7__ {int Connected; int ServerMode; void* RemotePort; int /*<<< orphan*/  RemoteIP; void* LocalPort; int /*<<< orphan*/  LocalIP; } ;
typedef  int /*<<< orphan*/  TUBE ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_1__* NewInProcSocket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 int /*<<< orphan*/  NewTubePair (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QuerySocketInformation (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseTube (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetIP (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTubeSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void NewSocketPair(SOCK **client, SOCK **server, IP *client_ip, UINT client_port, IP *server_ip, UINT server_port)
{
	IP iptmp;
	TUBE *t1, *t2;
	SOCK *sc, *ss;
	SOCK_EVENT *e1, *e2;
	// Validate arguments
	if (client == NULL || server == NULL)
	{
		return;
	}

	SetIP(&iptmp, 127, 0, 0, 1);
	if (client_ip == NULL)
	{
		client_ip = &iptmp;
	}
	if (server_ip == NULL)
	{
		server_ip = &iptmp;
	}

	// Creating a tube
	NewTubePair(&t1, &t2, 0);	// t1: C -> S,  t2: S -> C

	// Creating a socket event
	e1 = NewSockEvent();
	e2 = NewSockEvent();

	SetTubeSockEvent(t1, e1);
	SetTubeSockEvent(t2, e2);

	sc = NewInProcSocket(t1, t2);
	ss = NewInProcSocket(t2, t1);

	Copy(&sc->LocalIP, client_ip, sizeof(IP));
	sc->LocalPort = client_port;
	Copy(&sc->RemoteIP, server_ip, sizeof(IP));
	sc->RemotePort = server_port;

	Copy(&ss->LocalIP, server_ip, sizeof(IP));
	ss->LocalPort = server_port;
	Copy(&ss->RemoteIP, client_ip, sizeof(IP));
	ss->RemotePort = client_port;

	sc->Connected = true;
	sc->ServerMode = false;

	ss->Connected = true;
	ss->ServerMode = true;

	SetTimeout(sc, INFINITE);
	SetTimeout(ss, INFINITE);

	QuerySocketInformation(sc);
	QuerySocketInformation(ss);

	ReleaseSockEvent(e1);
	ReleaseSockEvent(e2);

	ReleaseTube(t1);
	ReleaseTube(t2);

	*client = sc;
	*server = ss;
}