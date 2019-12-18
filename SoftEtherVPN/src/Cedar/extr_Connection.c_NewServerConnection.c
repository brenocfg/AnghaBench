#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Server; int /*<<< orphan*/  ServerStr; int /*<<< orphan*/  Build; int /*<<< orphan*/  Version; int /*<<< orphan*/  ref; } ;
struct TYPE_13__ {int ServerMode; int IsInProc; void* SendBlocks2; void* SendBlocks; void* ReceivedBlocks; int /*<<< orphan*/  ServerX; int /*<<< orphan*/  ServerStr; int /*<<< orphan*/  ServerBuild; int /*<<< orphan*/  ServerVer; int /*<<< orphan*/  CurrentNumConnection; TYPE_2__* Thread; int /*<<< orphan*/  Name; int /*<<< orphan*/  Status; TYPE_1__* Tcp; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  ClientIp; TYPE_3__* FirstSock; int /*<<< orphan*/  Type; int /*<<< orphan*/  Protocol; TYPE_5__* Cedar; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; int /*<<< orphan*/  ConnectedTick; } ;
struct TYPE_12__ {scalar_t__ Type; int /*<<< orphan*/ * RemoteX; int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RemoteIP; int /*<<< orphan*/  ref; } ;
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int /*<<< orphan*/  TcpSockList; } ;
typedef  TYPE_2__ THREAD ;
typedef  int /*<<< orphan*/  TCP ;
typedef  TYPE_3__ SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_4__ CONNECTION ;
typedef  TYPE_5__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTION_STATUS_ACCEPTED ; 
 int /*<<< orphan*/  CONNECTION_TCP ; 
 int /*<<< orphan*/  CONNECTION_TYPE_INIT ; 
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  GetServerProductName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewCounter () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewLock () ; 
 void* NewQueue () ; 
 int /*<<< orphan*/  NewRef () ; 
 scalar_t__ SOCK_INPROC ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 
 void* ZeroMalloc (int) ; 

CONNECTION *NewServerConnection(CEDAR *cedar, SOCK *s, THREAD *t)
{
	CONNECTION *c;
	// Validate arguments
	if (cedar == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(CONNECTION));
	c->ConnectedTick = Tick64();
	c->lock = NewLock();
	c->ref = NewRef();
	c->Cedar = cedar;
	AddRef(c->Cedar->ref);
	c->Protocol = CONNECTION_TCP;
	c->Type = CONNECTION_TYPE_INIT;
	c->FirstSock = s;
	if (s != NULL)
	{
		AddRef(c->FirstSock->ref);
		Copy(&c->ClientIp, &s->RemoteIP, sizeof(IP));
		StrCpy(c->ClientHostname, sizeof(c->ClientHostname), s->RemoteHostname);
	}
	c->Tcp = ZeroMalloc(sizeof(TCP));
	c->Tcp->TcpSockList = NewList(NULL);
	c->ServerMode = true;
	c->Status = CONNECTION_STATUS_ACCEPTED;
	c->Name = CopyStr("INITING");
	c->Thread = t;
	AddRef(t->ref);
	c->CurrentNumConnection = NewCounter();
	Inc(c->CurrentNumConnection);

	c->ServerVer = cedar->Version;
	c->ServerBuild = cedar->Build;
	StrCpy(c->ServerStr, sizeof(c->ServerStr), cedar->ServerStr);
	GetServerProductName(cedar->Server, c->ServerStr, sizeof(c->ServerStr));

	if (s != NULL && s->RemoteX != NULL)
	{
		c->ServerX = CloneX(s->RemoteX);
	}

	if (s != NULL && s->Type == SOCK_INPROC)
	{
		// In-process socket
		c->IsInProc = true;
	}

	// Creating a Queue
	c->ReceivedBlocks = NewQueue();
	c->SendBlocks = NewQueue();
	c->SendBlocks2 = NewQueue();

	return c;
}