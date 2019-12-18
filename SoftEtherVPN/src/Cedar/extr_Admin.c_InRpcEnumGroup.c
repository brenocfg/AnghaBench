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
struct TYPE_7__ {int NumGroup; TYPE_1__* Groups; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {int /*<<< orphan*/  DenyAccess; int /*<<< orphan*/  NumUsers; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_GROUP_ITEM ;
typedef  TYPE_2__ RPC_ENUM_GROUP ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  PackGetUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumGroup(RPC_ENUM_GROUP *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_GROUP));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->NumGroup = PackGetIndexCount(p, "Name");
	t->Groups = ZeroMalloc(sizeof(RPC_ENUM_GROUP_ITEM) * t->NumGroup);

	for (i = 0;i < t->NumGroup;i++)
	{
		RPC_ENUM_GROUP_ITEM *e = &t->Groups[i];

		PackGetStrEx(p, "Name", e->Name, sizeof(e->Name), i);
		PackGetUniStrEx(p, "Realname", e->Realname, sizeof(e->Realname), i);
		PackGetUniStrEx(p, "Note", e->Note, sizeof(e->Note), i);
		e->NumUsers = PackGetIntEx(p, "NumUsers", i);
		e->DenyAccess = PackGetBoolEx(p, "DenyAccess", i);
	}
}