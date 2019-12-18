#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_12__ {int ServerMode; void* SendBlocks2; void* SendBlocks; void* ReceivedBlocks; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  ClientStr; void* ClientBuild; void* ClientVer; TYPE_4__* Session; void* ConnectingSocks; void* ConnectingThreads; int /*<<< orphan*/  CurrentNumConnection; void* LastCounterResetTick; int /*<<< orphan*/  Name; int /*<<< orphan*/  Status; TYPE_1__* Tcp; int /*<<< orphan*/  Protocol; TYPE_2__* Cedar; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; void* ConnectedTick; } ;
struct TYPE_11__ {int VirtualHost; int LinkModeClient; TYPE_3__* ClientOption; TYPE_2__* Cedar; } ;
struct TYPE_10__ {char* Hostname; int /*<<< orphan*/  Port; } ;
struct TYPE_9__ {void* Build; void* Version; int /*<<< orphan*/  ref; } ;
struct TYPE_8__ {void* TcpSockList; } ;
typedef  int /*<<< orphan*/  TCP ;
typedef  TYPE_4__ SESSION ;
typedef  TYPE_5__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 char* CEDAR_CLIENT_STR ; 
 char* CEDAR_ROUTER_STR ; 
 char* CEDAR_SERVER_LINK_STR ; 
 int /*<<< orphan*/  CONNECTION_STATUS_CONNECTING ; 
 int /*<<< orphan*/  CONNECTION_TCP ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewCounter () ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewLock () ; 
 void* NewQueue () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 void* Tick64 () ; 
 void* ZeroMalloc (int) ; 

CONNECTION *NewClientConnectionEx(SESSION *s, char *client_str, UINT client_ver, UINT client_build)
{
	CONNECTION *c;

	// Initialization of CONNECTION object
	c = ZeroMalloc(sizeof(CONNECTION));
	c->ConnectedTick = Tick64();
	c->lock = NewLock();
	c->ref = NewRef();
	c->Cedar = s->Cedar;
	AddRef(c->Cedar->ref);
	c->Protocol = CONNECTION_TCP;
	c->Tcp = ZeroMalloc(sizeof(TCP));
	c->Tcp->TcpSockList = NewList(NULL);
	c->ServerMode = false;
	c->Status = CONNECTION_STATUS_CONNECTING;
	c->Name = CopyStr("CLIENT_CONNECTION");
	c->Session = s;
	c->CurrentNumConnection = NewCounter();
	c->LastCounterResetTick = Tick64();
	Inc(c->CurrentNumConnection);

	c->ConnectingThreads = NewList(NULL);
	c->ConnectingSocks = NewList(NULL);

	if (client_str == NULL)
	{
		c->ClientVer = s->Cedar->Version;
		c->ClientBuild = s->Cedar->Build;

		if (c->Session->VirtualHost == false)
		{
			if (c->Session->LinkModeClient == false)
			{
				StrCpy(c->ClientStr, sizeof(c->ClientStr), CEDAR_CLIENT_STR);
			}
			else
			{
				StrCpy(c->ClientStr, sizeof(c->ClientStr), CEDAR_SERVER_LINK_STR);
			}
		}
		else
		{
			StrCpy(c->ClientStr, sizeof(c->ClientStr), CEDAR_ROUTER_STR);
		}
	}
	else
	{
		c->ClientVer = client_ver;
		c->ClientBuild = client_build;
		StrCpy(c->ClientStr, sizeof(c->ClientStr), client_str);
	}

	// Server name and port number
	StrCpy(c->ServerName, sizeof(c->ServerName), s->ClientOption->Hostname);
	c->ServerPort = s->ClientOption->Port;

	// Create queues
	c->ReceivedBlocks = NewQueue();
	c->SendBlocks = NewQueue();
	c->SendBlocks2 = NewQueue();

	return c;
}