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
struct TYPE_19__ {int /*<<< orphan*/  MacHashTable; } ;
struct TYPE_18__ {int /*<<< orphan*/  VlanId; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  MacAddress; TYPE_1__* Session; } ;
struct TYPE_17__ {int NumMacTable; TYPE_3__* MacTables; int /*<<< orphan*/  HubName; } ;
struct TYPE_16__ {int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  VlanId; void* UpdatedTime; void* CreatedTime; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  Key; } ;
struct TYPE_15__ {int /*<<< orphan*/ * Cedar; } ;
struct TYPE_14__ {char* Name; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_ENUM_MAC_TABLE_ITEM ;
typedef  TYPE_4__ RPC_ENUM_MAC_TABLE ;
typedef  TYPE_5__ MAC_TABLE_ENTRY ;
typedef  TYPE_6__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t ERR_HUB_NOT_FOUND ; 
 size_t ERR_INTERNAL_ERROR ; 
 size_t ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (TYPE_5__**) ; 
 TYPE_6__* GetHub (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetMachineName (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HashListToArray (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  LockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POINTER_TO_KEY (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_6__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 void* TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 TYPE_3__* ZeroMalloc (int) ; 

UINT SiEnumMacTable(SERVER *s, char *hubname, RPC_ENUM_MAC_TABLE *t)
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

	LockHashList(h->MacHashTable);
	{
		MAC_TABLE_ENTRY **pp = (MAC_TABLE_ENTRY **)HashListToArray(h->MacHashTable, &t->NumMacTable);
		t->MacTables = ZeroMalloc(sizeof(RPC_ENUM_MAC_TABLE_ITEM) * t->NumMacTable);

		for (i = 0;i < t->NumMacTable;i++)
		{
			RPC_ENUM_MAC_TABLE_ITEM *e = &t->MacTables[i];
			MAC_TABLE_ENTRY *mac = pp[i];

			e->Key = POINTER_TO_KEY(mac);
			StrCpy(e->SessionName, sizeof(e->SessionName), mac->Session->Name);
			Copy(e->MacAddress, mac->MacAddress, sizeof(e->MacAddress));
			e->CreatedTime = TickToTime(mac->CreatedTime);
			e->UpdatedTime = TickToTime(mac->UpdatedTime);
			e->VlanId = mac->VlanId;

			GetMachineName(e->RemoteHostname, sizeof(e->RemoteHostname));
		}

		Free(pp);
	}
	UnlockHashList(h->MacHashTable);

	ReleaseHub(h);

	return ERR_NO_ERROR;
}