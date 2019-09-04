#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int Me; } ;
struct TYPE_15__ {int LastVersion; int CurrentVersion; int Offline; int /*<<< orphan*/  Type; int /*<<< orphan*/  Name; TYPE_1__* Cedar; } ;
struct TYPE_14__ {scalar_t__ ServerType; int /*<<< orphan*/ * FarmMemberList; } ;
struct TYPE_13__ {TYPE_2__* Server; } ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ HUB ;
typedef  TYPE_4__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int IsInList (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiCallUpdateHub (TYPE_2__*,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SiHubOnlineProc (TYPE_3__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void SiHubUpdateProc(HUB *h)
{
	SERVER *s;
	UINT i;
	// Validate arguments
	if (h == NULL || h->Cedar == NULL || h->Cedar->Server == NULL || h->Cedar->Server->ServerType != SERVER_TYPE_FARM_CONTROLLER)
	{
		return;
	}

	s = h->Cedar->Server;

	if (s->FarmMemberList == NULL)
	{
		return;
	}

	if (h->LastVersion != h->CurrentVersion || h->CurrentVersion == 0)
	{
		LIST *fm_list;
		if (h->CurrentVersion == 0)
		{
			h->CurrentVersion = 1;
		}
		h->LastVersion = h->CurrentVersion;

		Debug("SiHubUpdateProc HUB=%s, Ver=%u, Type=%u, Offline=%u\n", h->Name, h->CurrentVersion,
			h->Type, h->Offline);

		fm_list = NewListFast(NULL);

		LockList(s->FarmMemberList);
		{
			while (true)
			{
				bool escape = true;
				// Update the HUB on all members
				for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
				{
					FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

					if (IsInList(fm_list, f) == false)
					{
						Add(fm_list, f);
						escape = false;

						if (f->Me == false)
						{
							SiCallUpdateHub(s, f, h);
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

	if (h->Offline == false)
	{
		SiHubOnlineProc(h);
	}
}