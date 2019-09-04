#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {scalar_t__* Ports; int /*<<< orphan*/  HubList; int /*<<< orphan*/  TaskPostEvent; int /*<<< orphan*/  TaskQueue; scalar_t__ Point; scalar_t__ MaxSessions; scalar_t__ Weight; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/  hostname; scalar_t__ NumPort; scalar_t__ Ip; int /*<<< orphan*/  Cedar; } ;
struct TYPE_18__ {int /*<<< orphan*/  Cedar; int /*<<< orphan*/  FarmMemberList; } ;
struct TYPE_17__ {int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ HUB_LIST ;
typedef  TYPE_3__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CompareHubList ; 
 int /*<<< orphan*/  Debug (char*,char*,char*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ FARM_DEFAULT_WEIGHT ; 
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HttpServerSend (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr32 (char*,int,scalar_t__) ; 
 scalar_t__ IPToUINT (int /*<<< orphan*/ *) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_CONTROL_TCP_TIMEOUT ; 
 scalar_t__ SERVER_MAX_SESSIONS ; 
 int /*<<< orphan*/  SLog (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiFarmServMain (TYPE_2__*,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* ZeroMalloc (int) ; 

void SiFarmServ(SERVER *server, SOCK *sock, X *cert, UINT ip, UINT num_port, UINT *ports, char *hostname, UINT point, UINT weight, UINT max_sessions)
{
	PACK *p;
	FARM_MEMBER *f;
	UINT i;
	char tmp[MAX_SIZE];
	// Validate arguments
	if (server == NULL || sock == NULL || cert == NULL || num_port == 0 || ports == NULL || hostname == NULL)
	{
		return;
	}

	if (weight == 0)
	{
		weight = FARM_DEFAULT_WEIGHT;
	}

	if (max_sessions == 0)
	{
		max_sessions = SERVER_MAX_SESSIONS;
	}

	if (ip == 0)
	{
		// If the public IP address is not specified, specify the connection
		// source IP address of this farm member server
		ip = IPToUINT(&sock->RemoteIP);
	}

	IPToStr32(tmp, sizeof(tmp), ip);
	SLog(server->Cedar, "LS_FARM_SERV_START", tmp, hostname);

	// Inform the success
	p = NewPack();
	HttpServerSend(sock, p);
	FreePack(p);

	IPToStr32(tmp, sizeof(tmp), ip);
	Debug("Farm Member %s Connected. IP: %s\n", hostname, tmp);

	SetTimeout(sock, SERVER_CONTROL_TCP_TIMEOUT);

	f = ZeroMalloc(sizeof(FARM_MEMBER));
	f->Cedar = server->Cedar;
	f->Ip = ip;
	f->NumPort = num_port;
	f->Ports = ports;
	StrCpy(f->hostname, sizeof(f->hostname), hostname);
	f->ServerCert = cert;
	f->ConnectedTime = SystemTime64();
	f->Weight = weight;
	f->MaxSessions = max_sessions;

	f->HubList = NewList(CompareHubList);
	f->Point = point;

	f->TaskQueue = NewQueue();
	f->TaskPostEvent = NewEvent();

	// Add to the list
	LockList(server->FarmMemberList);
	{
		Add(server->FarmMemberList, f);
	}
	UnlockList(server->FarmMemberList);

	// Main process
	SiFarmServMain(server, sock, f);

	// Remove from the list
	LockList(server->FarmMemberList);
	{
		Delete(server->FarmMemberList, f);
	}
	UnlockList(server->FarmMemberList);

	ReleaseQueue(f->TaskQueue);
	ReleaseEvent(f->TaskPostEvent);

	for (i = 0;i < LIST_NUM(f->HubList);i++)
	{
		HUB_LIST *hh = LIST_DATA(f->HubList, i);
		Free(hh);
	}

	ReleaseList(f->HubList);

	Free(f);

	SLog(server->Cedar, "LS_FARM_SERV_END", hostname);
}