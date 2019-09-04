#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  CedarSuperLock; int /*<<< orphan*/ * HubList; } ;
struct TYPE_14__ {scalar_t__ NumSessions; int /*<<< orphan*/  ref; scalar_t__ AssignedBridgeLicense; scalar_t__ AssignedClientLicense; } ;
struct TYPE_13__ {scalar_t__ Halt; int /*<<< orphan*/ * FarmMemberList; scalar_t__ CurrentAssignedClientLicense; scalar_t__ CurrentAssignedBridgeLicense; scalar_t__ CurrentTotalNumSessionsOnFarm; int /*<<< orphan*/ * FarmControlThreadHaltEvent; TYPE_4__* Cedar; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_2__ FARM_MEMBER ;
typedef  int /*<<< orphan*/  EVENT ;
typedef  TYPE_4__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,int) ; 
 int IsInList (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVER_FARM_CONTROL_INTERVAL ; 
 int /*<<< orphan*/  SiCallEnumHub (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SiDebugLog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  SiHubUpdateProc (TYPE_2__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SiFarmControlThread(THREAD *thread, void *param)
{
	SERVER *s;
	CEDAR *c;
	EVENT *e;
	LIST *o;
	UINT i;
	char tmp[MAX_PATH];
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	s = (SERVER *)param;
	c = s->Cedar;
	e = s->FarmControlThreadHaltEvent;

	while (true)
	{
		Lock(c->CedarSuperLock);

		// Enumerate HUB list which is hosted by each farm member
		Format(tmp, sizeof(tmp), "CONTROLLER: %s %u", __FILE__, __LINE__);
		SiDebugLog(s, tmp);

		LockList(s->FarmMemberList);
		{
			UINT i;
			UINT num;
			UINT assigned_client_license = 0;
			UINT assigned_bridge_license = 0;
			LIST *fm_list = NewListFast(NULL);

			Format(tmp, sizeof(tmp), "CONTROLLER: %s %u", __FILE__, __LINE__);
			SiDebugLog(s, tmp);

			num = 0;

			while (true)
			{
				bool escape = true;
				for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
				{
					FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

					if (IsInList(fm_list, f) == false)
					{
						SiCallEnumHub(s, f);
						// Get the total number of sessions across the server farm
						num += f->NumSessions;

						assigned_client_license += f->AssignedClientLicense;
						assigned_bridge_license += f->AssignedBridgeLicense;

						escape = false;

						Add(fm_list, f);
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

			ReleaseList(fm_list);

			s->CurrentTotalNumSessionsOnFarm = num;

			// Update the number of assigned licenses
			s->CurrentAssignedBridgeLicense = assigned_bridge_license;
			s->CurrentAssignedClientLicense = assigned_client_license;

			Format(tmp, sizeof(tmp), "CONTROLLER: %s %u", __FILE__, __LINE__);
			SiDebugLog(s, tmp);
		}
		UnlockList(s->FarmMemberList);

		Format(tmp, sizeof(tmp), "CONTROLLER: %s %u", __FILE__, __LINE__);
		SiDebugLog(s, tmp);

		o = NewListFast(NULL);

		Format(tmp, sizeof(tmp), "CONTROLLER: %s %u", __FILE__, __LINE__);
		SiDebugLog(s, tmp);

		// Emit an update notification for each HUB
		LockList(c->HubList);
		{
			UINT i;
			for (i = 0;i < LIST_NUM(c->HubList);i++)
			{
				HUB *h = LIST_DATA(c->HubList, i);
				AddRef(h->ref);
				Add(o, h);
			}
		}
		UnlockList(c->HubList);

		Format(tmp, sizeof(tmp), "CONTROLLER: %s %u", __FILE__, __LINE__);
		SiDebugLog(s, tmp);

		for (i = 0;i < LIST_NUM(o);i++)
		{
			HUB *h = LIST_DATA(o, i);
			SiHubUpdateProc(h);
			ReleaseHub(h);
		}

		Format(tmp, sizeof(tmp), "CONTROLLER: %s %u", __FILE__, __LINE__);
		SiDebugLog(s, tmp);

		ReleaseList(o);

		Unlock(c->CedarSuperLock);

		Wait(e, SERVER_FARM_CONTROL_INTERVAL);
		if (s->Halt)
		{
			break;
		}
	}
}