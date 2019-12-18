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
struct TYPE_7__ {int NumLink; TYPE_1__* Links; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {int /*<<< orphan*/  HubName; int /*<<< orphan*/  LastError; void* Connected; int /*<<< orphan*/  ConnectedTime; void* Online; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_ENUM_LINK_ITEM ;
typedef  TYPE_2__ RPC_ENUM_LINK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  PackGetUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumLink(RPC_ENUM_LINK *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_LINK));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->NumLink = PackGetIndexCount(p, "AccountName");
	t->Links = ZeroMalloc(sizeof(RPC_ENUM_LINK_ITEM) * t->NumLink);

	for (i = 0;i < t->NumLink;i++)
	{
		RPC_ENUM_LINK_ITEM *e = &t->Links[i];

		PackGetUniStrEx(p, "AccountName", e->AccountName, sizeof(e->AccountName), i);
		PackGetStrEx(p, "Hostname", e->Hostname, sizeof(e->Hostname), i);
		PackGetStrEx(p, "ConnectedHubName", e->HubName, sizeof(e->HubName), i);
		e->Online = PackGetBoolEx(p, "Online", i);
		e->ConnectedTime = PackGetInt64Ex(p, "ConnectedTime", i);
		e->Connected = PackGetBoolEx(p, "Connected", i);
		e->LastError = PackGetIntEx(p, "LastError", i);
		PackGetStrEx(p, "LinkHubName", e->HubName, sizeof(e->HubName), i);
	}
}