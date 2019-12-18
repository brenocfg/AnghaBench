#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_19__ {int /*<<< orphan*/  IpTable; } ;
struct TYPE_18__ {int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  DhcpAllocated; int /*<<< orphan*/  Ip; TYPE_1__* Session; } ;
struct TYPE_17__ {int NumIpTable; TYPE_3__* IpTables; int /*<<< orphan*/  HubName; } ;
struct TYPE_16__ {int /*<<< orphan*/  RemoteHostname; void* UpdatedTime; void* CreatedTime; int /*<<< orphan*/  DhcpAllocated; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  IpV6; int /*<<< orphan*/  Ip; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  Key; } ;
struct TYPE_15__ {int /*<<< orphan*/ * Cedar; } ;
struct TYPE_14__ {char* Name; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_ENUM_IP_TABLE_ITEM ;
typedef  TYPE_4__ RPC_ENUM_IP_TABLE ;
typedef  TYPE_5__ IP_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_6__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t ERR_HUB_NOT_FOUND ; 
 size_t ERR_INTERNAL_ERROR ; 
 size_t ERR_NO_ERROR ; 
 TYPE_6__* GetHub (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetMachineName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 TYPE_5__* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POINTER_TO_KEY (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_6__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 void* TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* ZeroMalloc (int) ; 

UINT SiEnumIpTable(SERVER *s, char *hubname, RPC_ENUM_IP_TABLE *t)
{
	CEDAR *c;
	UINT i;
	HUB *h = NULL;
	// Validate arguments
	if (s == NULL || hubname == NULL || t == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	c = s->Cedar;

	LockHubList(c);
	{
		h = GetHub(c, hubname);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	StrCpy(t->HubName, sizeof(t->HubName), hubname);

	LockList(h->IpTable);
	{
		t->NumIpTable = LIST_NUM(h->IpTable);
		t->IpTables = ZeroMalloc(sizeof(RPC_ENUM_IP_TABLE_ITEM) * t->NumIpTable);

		for (i = 0;i < t->NumIpTable;i++)
		{
			RPC_ENUM_IP_TABLE_ITEM *e = &t->IpTables[i];
			IP_TABLE_ENTRY *table = LIST_DATA(h->IpTable, i);

			e->Key = POINTER_TO_KEY(table);
			StrCpy(e->SessionName, sizeof(e->SessionName), table->Session->Name);
			e->Ip = IPToUINT(&table->Ip);
			Copy(&e->IpV6, &table->Ip, sizeof(IP));
			Copy(&e->IpAddress, &table->Ip, sizeof(IP));
			e->DhcpAllocated = table->DhcpAllocated;
			e->CreatedTime = TickToTime(table->CreatedTime);
			e->UpdatedTime = TickToTime(table->UpdatedTime);

			GetMachineName(e->RemoteHostname, sizeof(e->RemoteHostname));
		}
	}
	UnlockList(h->IpTable);

	ReleaseHub(h);

	return ERR_NO_ERROR;
}