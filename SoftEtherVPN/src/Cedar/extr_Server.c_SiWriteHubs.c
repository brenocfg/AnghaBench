#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_11__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; } ;
struct TYPE_9__ {TYPE_3__* Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_2__**) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteHubCfg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YieldCpu () ; 

void SiWriteHubs(FOLDER *f, SERVER *s)
{
	UINT i;
	FOLDER *hub_folder;
	CEDAR *c;
	UINT num;
	HUB **hubs;
	// Validate arguments
	if (f == NULL || s == NULL)
	{
		return;
	}
	c = s->Cedar;

	LockList(c->HubList);
	{
		hubs = ToArray(c->HubList);
		num = LIST_NUM(c->HubList);

		for (i = 0;i < num;i++)
		{
			AddRef(hubs[i]->ref);
		}
	}
	UnlockList(c->HubList);

	for (i = 0;i < num;i++)
	{
		HUB *h = hubs[i];

		Lock(h->lock);
		{
			hub_folder = CfgCreateFolder(f, h->Name);
			SiWriteHubCfg(hub_folder, h);
		}
		Unlock(h->lock);

		ReleaseHub(h);

		if ((i % 30) == 1)
		{
			YieldCpu();
		}
	}

	Free(hubs);
}