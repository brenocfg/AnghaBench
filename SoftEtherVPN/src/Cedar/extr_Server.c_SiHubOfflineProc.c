#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Name; TYPE_1__* Cedar; } ;
struct TYPE_8__ {scalar_t__ ServerType; int /*<<< orphan*/ * FarmMemberList; } ;
struct TYPE_7__ {TYPE_2__* Server; } ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsInList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiCallDeleteHub (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void SiHubOfflineProc(HUB *h)
{
	SERVER *s;
	char hubname[MAX_HUBNAME_LEN + 1];
	UINT i;
	LIST *fm_list;
	// Validate arguments
	if (h == NULL || h->Cedar->Server == NULL || h->Cedar->Server->ServerType != SERVER_TYPE_FARM_CONTROLLER)
	{
		// Process only on the farm controller
		return;
	}

	s = h->Cedar->Server;

	if (s->FarmMemberList == NULL)
	{
		return;
	}

	StrCpy(hubname, sizeof(hubname), h->Name);

	fm_list = NewListFast(NULL);

	LockList(s->FarmMemberList);
	{
		while (true)
		{
			bool escape = true;

			// Stop the HUB on all members
			for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
			{
				FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

				if (IsInList(fm_list, f) == false)
				{
					Add(fm_list, f);
					escape = false;

					SiCallDeleteHub(s, f, h);

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