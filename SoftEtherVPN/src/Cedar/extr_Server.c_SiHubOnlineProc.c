#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int /*<<< orphan*/ * HubList; } ;
struct TYPE_13__ {scalar_t__ Type; int /*<<< orphan*/  Name; TYPE_1__* Cedar; } ;
struct TYPE_12__ {int /*<<< orphan*/  Name; } ;
struct TYPE_11__ {scalar_t__ ServerType; int /*<<< orphan*/ * FarmMemberList; } ;
struct TYPE_10__ {TYPE_2__* Server; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ HUB_LIST ;
typedef  TYPE_4__ HUB ;
typedef  TYPE_5__ FARM_MEMBER ;

/* Variables and functions */
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiCallCreateHub (TYPE_2__*,TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void SiHubOnlineProc(HUB *h)
{
	SERVER *s;
	UINT i;
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

	LockList(s->FarmMemberList);
	{
		if (h->Type == HUB_TYPE_FARM_STATIC)
		{
			// Static HUB
			// Create the HUB on all members
			for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
			{
				UINT j;
				bool exists = false;
				FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

				LockList(f->HubList);
				{
					for (j = 0;j < LIST_NUM(f->HubList);j++)
					{
						HUB_LIST *hh = LIST_DATA(f->HubList, j);
						if (StrCmpi(hh->Name, h->Name) == 0)
						{
							exists = true;
						}
					}
				}
				UnlockList(f->HubList);

				if (exists == false)
				{
					SiCallCreateHub(s, f, h);
				}
			}
		}
	}
	UnlockList(s->FarmMemberList);
}