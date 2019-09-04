#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tt ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_17__ {TYPE_2__* Server; } ;
struct TYPE_16__ {int /*<<< orphan*/  ConnectionList; } ;
struct TYPE_15__ {char* Name; char* Hostname; char* ServerStr; char* ClientStr; int /*<<< orphan*/  lock; int /*<<< orphan*/  ClientBuild; int /*<<< orphan*/  ClientVer; int /*<<< orphan*/  ServerBuild; int /*<<< orphan*/  ServerVer; int /*<<< orphan*/  Type; int /*<<< orphan*/  ConnectedTick; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Port; int /*<<< orphan*/  Ip; TYPE_1__* FirstSock; int /*<<< orphan*/  ref; } ;
struct TYPE_14__ {TYPE_5__* Cedar; } ;
struct TYPE_13__ {char* RemoteHostname; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_CONNECTION_INFO ;
typedef  TYPE_3__ CONNECTION ;
typedef  TYPE_5__ CEDAR ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_CONNECTION_NAME_LEN ; 
 int /*<<< orphan*/  ReleaseConnection (TYPE_3__*) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 TYPE_3__* Search (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

UINT StGetConnectionInfo(ADMIN *a, RPC_CONNECTION_INFO *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	CONNECTION *connection;
	char name[MAX_CONNECTION_NAME_LEN + 1];

	if (IsEmptyStr(t->Name))
	{
		return ERR_INVALID_PARAMETER;
	}

	SERVER_ADMIN_ONLY;

	LockList(c->ConnectionList);
	{
		CONNECTION tt;
		Zero(&tt, sizeof(tt));
		tt.Name = t->Name;
		StrCpy(name, sizeof(name), t->Name);

		connection = Search(c->ConnectionList, &tt);

		if (connection != NULL)
		{
			AddRef(connection->ref);
		}
	}
	UnlockList(c->ConnectionList);

	if (connection == NULL)
	{
		return ERR_OBJECT_NOT_FOUND;
	}

	Zero(t, sizeof(RPC_CONNECTION_INFO));
	StrCpy(t->Name, sizeof(t->Name), name);

	Lock(connection->lock);
	{
		SOCK *s = connection->FirstSock;

		if (s != NULL)
		{
			t->Ip = IPToUINT(&s->RemoteIP);
			t->Port = s->RemotePort;
			StrCpy(t->Hostname, sizeof(t->Hostname), s->RemoteHostname);
		}

		StrCpy(t->Name, sizeof(t->Name), connection->Name);
		t->ConnectedTime = TickToTime(connection->ConnectedTick);
		t->Type = connection->Type;

		StrCpy(t->ServerStr, sizeof(t->ServerStr), connection->ServerStr);
		StrCpy(t->ClientStr, sizeof(t->ClientStr), connection->ClientStr);
		t->ServerVer = connection->ServerVer;
		t->ServerBuild = connection->ServerBuild;
		t->ClientVer = connection->ClientVer;
		t->ClientBuild = connection->ClientBuild;
	}
	Unlock(connection->lock);

	ReleaseConnection(connection);

	return ERR_NO_ERROR;
}