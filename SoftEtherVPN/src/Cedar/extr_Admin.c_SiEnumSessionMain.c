#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  hubname ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int Me; } ;
struct TYPE_19__ {char* HubName; } ;
struct TYPE_18__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmMemberList; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ENUM_SESSION ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  AdjoinRpcEnumSession (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumSession (TYPE_2__*) ; 
 int IsInList (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiCallEnumSession (TYPE_1__*,TYPE_3__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  SiEnumLocalSession (TYPE_1__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void SiEnumSessionMain(SERVER *s, RPC_ENUM_SESSION *t)
{
	char hubname[MAX_HUBNAME_LEN + 1];
	UINT ret = ERR_NO_ERROR;
	UINT num;
	UINT i;
	// Validate arguments
	if (s == NULL || t == NULL)
	{
		return;
	}

	StrCpy(hubname, sizeof(hubname), t->HubName);

	FreeRpcEnumSession(t);
	Zero(t, sizeof(RPC_ENUM_SESSION));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);

	// Local session enumeration
	num = 0;
	SiEnumLocalSession(s, hubname, t);

	if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		LIST *fm_list;

		fm_list = NewListFast(NULL);

		// Remote session enumeration
		LockList(s->FarmMemberList);
		{
			while (true)
			{
				bool escape = true;

				for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
				{
					FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

					if (IsInList(fm_list, f) == false)
					{
						Add(fm_list, f);
						escape = false;

						if (f->Me == false)
						{
							RPC_ENUM_SESSION tmp;

							Zero(&tmp, sizeof(tmp));

							SiCallEnumSession(s, f, hubname, &tmp);

							AdjoinRpcEnumSession(t, &tmp);
							FreeRpcEnumSession(&tmp);
						}

						break;
					}
				}

				if (escape)
				{
					break;
				}

				UnlockList(s->FarmMemberList);
				LockList(s->FarmMemberList);
			}
		}
		UnlockList(s->FarmMemberList);

		ReleaseList(fm_list);
	}
}