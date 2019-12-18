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
struct TYPE_7__ {int NumCa; TYPE_1__* Ca; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {int /*<<< orphan*/  Expires; int /*<<< orphan*/  IssuerName; int /*<<< orphan*/  SubjectName; int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ RPC_HUB_ENUM_CA_ITEM ;
typedef  TYPE_2__ RPC_HUB_ENUM_CA ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcHubEnumCa(RPC_HUB_ENUM_CA *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_HUB_ENUM_CA));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->NumCa = PackGetIndexCount(p, "Key");
	t->Ca = ZeroMalloc(sizeof(RPC_HUB_ENUM_CA_ITEM) * t->NumCa);

	for (i = 0;i < t->NumCa;i++)
	{
		RPC_HUB_ENUM_CA_ITEM *e = &t->Ca[i];

		e->Key = PackGetIntEx(p, "Key", i);
		PackGetUniStrEx(p, "SubjectName", e->SubjectName, sizeof(e->SubjectName), i);
		PackGetUniStrEx(p, "IssuerName", e->IssuerName, sizeof(e->IssuerName), i);
		e->Expires = PackGetInt64Ex(p, "Expires", i);
	}
}