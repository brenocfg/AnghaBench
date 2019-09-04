#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  hubname ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {TYPE_1__* Server; } ;
struct TYPE_19__ {int Me; } ;
struct TYPE_18__ {int /*<<< orphan*/  HubName; } ;
struct TYPE_17__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmMemberList; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ENUM_MAC_TABLE ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_3__ FARM_MEMBER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  AdjoinRpcEnumMacTable (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumMacTable (TYPE_2__*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiCallEnumMacTable (TYPE_1__*,TYPE_3__*,char*,TYPE_2__*) ; 
 scalar_t__ SiEnumMacTable (TYPE_1__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT StEnumMacTable(ADMIN *a, RPC_ENUM_MAC_TABLE *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;
	char hubname[MAX_HUBNAME_LEN + 1];
	UINT i;

	CHECK_RIGHT;

	// Get local MAC address table
	StrCpy(hubname, sizeof(hubname), t->HubName);
	FreeRpcEnumMacTable(t);
	Zero(t, sizeof(RPC_ENUM_MAC_TABLE));

	ret = SiEnumMacTable(s, hubname, t);
	if (ret != ERR_NO_ERROR)
	{
		return ret;
	}

	if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		// Get remote MAC address table
		LockList(s->FarmMemberList);
		{
			for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
			{
				FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);
				if (f->Me == false)
				{
					RPC_ENUM_MAC_TABLE tmp;

					Zero(&tmp, sizeof(tmp));

					SiCallEnumMacTable(s, f, hubname, &tmp);

					AdjoinRpcEnumMacTable(t, &tmp);
					FreeRpcEnumMacTable(&tmp);
				}
			}
		}
		UnlockList(s->FarmMemberList);
	}

	return ret;
}