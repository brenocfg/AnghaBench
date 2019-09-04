#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int Me; int /*<<< orphan*/  HubList; } ;
struct TYPE_13__ {scalar_t__ Type; int /*<<< orphan*/  Name; } ;
struct TYPE_12__ {int DynamicHub; int /*<<< orphan*/  Name; TYPE_3__* FarmMember; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ HUB_LIST ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_3__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/ * SiCallTask (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiPackAddCreateHub (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void SiCallCreateHub(SERVER *s, FARM_MEMBER *f, HUB *h)
{
	PACK *p;
	HUB_LIST *hh;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	if (f->Me == false)
	{
		p = NewPack();

		SiPackAddCreateHub(p, h);

		p = SiCallTask(f, p, "createhub");
		FreePack(p);
	}

	hh = ZeroMalloc(sizeof(HUB_LIST));
	hh->DynamicHub = (h->Type == HUB_TYPE_FARM_DYNAMIC ? true : false);
	StrCpy(hh->Name, sizeof(hh->Name), h->Name);
	hh->FarmMember = f;

	LockList(f->HubList);
	{
		bool exists = false;
		UINT i;
		for (i = 0;i < LIST_NUM(f->HubList);i++)
		{
			HUB_LIST *t = LIST_DATA(f->HubList, i);
			if (StrCmpi(t->Name, hh->Name) == 0)
			{
				exists = true;
			}
		}
		if (exists == false)
		{
			Add(f->HubList, hh);
		}
		else
		{
			Free(hh);
		}
	}
	UnlockList(f->HubList);
}