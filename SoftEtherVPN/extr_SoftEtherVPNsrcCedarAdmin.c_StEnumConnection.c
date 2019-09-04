#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_20__ {TYPE_2__* Server; } ;
struct TYPE_19__ {int /*<<< orphan*/  ConnectionList; } ;
struct TYPE_18__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Type; int /*<<< orphan*/  ConnectedTick; int /*<<< orphan*/  Name; TYPE_1__* FirstSock; } ;
struct TYPE_17__ {int NumConnection; TYPE_3__* Connections; } ;
struct TYPE_16__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Name; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Port; int /*<<< orphan*/  Ip; } ;
struct TYPE_15__ {TYPE_6__* Cedar; } ;
struct TYPE_14__ {int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_ENUM_CONNECTION_ITEM ;
typedef  TYPE_4__ RPC_ENUM_CONNECTION ;
typedef  TYPE_5__ CONNECTION ;
typedef  TYPE_6__ CEDAR ;
typedef  TYPE_7__ ADMIN ;

/* Variables and functions */
 size_t ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumConnection (TYPE_4__*) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 TYPE_5__* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 
 TYPE_3__* ZeroMalloc (int) ; 

UINT StEnumConnection(ADMIN *a, RPC_ENUM_CONNECTION *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;

	SERVER_ADMIN_ONLY;

	FreeRpcEnumConnection(t);
	Zero(t, sizeof(RPC_ENUM_CONNECTION));

	LockList(c->ConnectionList);
	{
		UINT i;
		t->NumConnection = LIST_NUM(c->ConnectionList);
		t->Connections = ZeroMalloc(sizeof(RPC_ENUM_CONNECTION_ITEM) * t->NumConnection);
		
		for (i = 0;i < t->NumConnection;i++)
		{
			RPC_ENUM_CONNECTION_ITEM *e = &t->Connections[i];
			CONNECTION *connection = LIST_DATA(c->ConnectionList, i);

			Lock(connection->lock);
			{
				SOCK *s = connection->FirstSock;

				if (s != NULL)
				{
					e->Ip = IPToUINT(&s->RemoteIP);
					e->Port = s->RemotePort;
					StrCpy(e->Hostname, sizeof(e->Hostname), s->RemoteHostname);
				}

				StrCpy(e->Name, sizeof(e->Name), connection->Name);
				e->ConnectedTime = TickToTime(connection->ConnectedTick);
				e->Type = connection->Type;
			}
			Unlock(connection->lock);
		}
	}
	UnlockList(c->ConnectionList);

	return ERR_NO_ERROR;
}