#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {int Me; int /*<<< orphan*/  HubList; } ;
struct TYPE_11__ {int /*<<< orphan*/  Name; } ;
struct TYPE_10__ {int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ HUB_LIST ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_3__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SiCallTask (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SiCallDeleteHub(SERVER *s, FARM_MEMBER *f, HUB *h)
{
	PACK *p;
	UINT i;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	if (f->Me == false)
	{
		p = NewPack();

		PackAddStr(p, "HubName", h->Name);

		p = SiCallTask(f, p, "deletehub");
		FreePack(p);
	}

	LockList(f->HubList);
	{
		for (i = 0;i < LIST_NUM(f->HubList);i++)
		{
			HUB_LIST *hh = LIST_DATA(f->HubList, i);
			if (StrCmpi(hh->Name, h->Name) == 0)
			{
				Free(hh);
				Delete(f->HubList, hh);
			}
		}
	}
	UnlockList(f->HubList);
}