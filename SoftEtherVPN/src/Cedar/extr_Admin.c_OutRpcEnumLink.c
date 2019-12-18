#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t NumLink; TYPE_1__* Links; int /*<<< orphan*/  HubName; } ;
struct TYPE_4__ {int /*<<< orphan*/  HubName; int /*<<< orphan*/  LastError; int /*<<< orphan*/  Connected; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Online; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_ENUM_LINK_ITEM ;
typedef  TYPE_2__ RPC_ENUM_LINK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumLink(PACK *p, RPC_ENUM_LINK *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "LinkList");
	for (i = 0;i < t->NumLink;i++)
	{
		RPC_ENUM_LINK_ITEM *e = &t->Links[i];

		PackAddUniStrEx(p, "AccountName", e->AccountName, i, t->NumLink);
		PackAddStrEx(p, "ConnectedHubName", e->HubName, i, t->NumLink);
		PackAddStrEx(p, "Hostname", e->Hostname, i, t->NumLink);
		PackAddBoolEx(p, "Online", e->Online, i, t->NumLink);
		PackAddTime64Ex(p, "ConnectedTime", e->ConnectedTime, i, t->NumLink);
		PackAddBoolEx(p, "Connected", e->Connected, i, t->NumLink);
		PackAddIntEx(p, "LastError", e->LastError, i, t->NumLink);
		PackAddStrEx(p, "TargetHubName", e->HubName, i, t->NumLink);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}