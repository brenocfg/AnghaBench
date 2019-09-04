#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_11__ {int /*<<< orphan*/  hostname; } ;
struct TYPE_10__ {size_t NumIpTable; TYPE_1__* IpTables; } ;
struct TYPE_9__ {int RemoteItem; int /*<<< orphan*/  RemoteHostname; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_2__ RPC_ENUM_IP_TABLE ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcEnumIpTable (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * SiCallTask (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void SiCallEnumIpTable(SERVER *s, FARM_MEMBER *f, char *hubname, RPC_ENUM_IP_TABLE *t)
{
	PACK *p;
	UINT i;
	// Validate arguments
	if (s == NULL || f == NULL || hubname == NULL || t == NULL)
	{
		return;
	}

	p = NewPack();
	PackAddStr(p, "HubName", hubname);

	p = SiCallTask(f, p, "enumiptable");

	Zero(t, sizeof(RPC_ENUM_IP_TABLE));
	InRpcEnumIpTable(t, p);

	for (i = 0;i < t->NumIpTable;i++)
	{
		t->IpTables[i].RemoteItem = true;
		StrCpy(t->IpTables[i].RemoteHostname, sizeof(t->IpTables[i].RemoteHostname),
			f->hostname);
	}

	FreePack(p);
}