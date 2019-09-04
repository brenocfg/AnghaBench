#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {int NumConnection; TYPE_1__* Connections; } ;
struct TYPE_6__ {void* Type; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Name; void* Port; int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ RPC_ENUM_CONNECTION_ITEM ;
typedef  TYPE_2__ RPC_ENUM_CONNECTION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIp32Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumConnection(RPC_ENUM_CONNECTION *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_CONNECTION));
	t->NumConnection = PackGetIndexCount(p, "Name");
	t->Connections = ZeroMalloc(sizeof(RPC_ENUM_CONNECTION_ITEM) * t->NumConnection);

	for (i = 0;i < t->NumConnection;i++)
	{
		RPC_ENUM_CONNECTION_ITEM *e = &t->Connections[i];

		e->Ip = PackGetIp32Ex(p, "Ip", i);
		e->Port = PackGetIntEx(p, "Port", i);
		PackGetStrEx(p, "Name", e->Name, sizeof(e->Name), i);
		PackGetStrEx(p, "Hostname", e->Hostname, sizeof(e->Hostname), i);
		e->ConnectedTime = PackGetInt64Ex(p, "ConnectedTime", i);
		e->Type = PackGetIntEx(p, "Type", i);
	}
}