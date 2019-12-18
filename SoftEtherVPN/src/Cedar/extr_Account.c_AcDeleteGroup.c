#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USERGROUP ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * Group; } ;
typedef  TYPE_2__ USER ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {TYPE_1__* HubDb; } ;
struct TYPE_8__ {int /*<<< orphan*/  UserList; int /*<<< orphan*/  GroupList; } ;
typedef  TYPE_3__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * AcGetGroup (TYPE_3__*,char*) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinUserToGroup (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

bool AcDeleteGroup(HUB *h, char *name)
{
	USERGROUP *g;
	UINT i;
	// Validate arguments
	if (h == NULL || name == NULL)
	{
		return false;
	}

	g = AcGetGroup(h, name);
	if (g == NULL)
	{
		return false;
	}

	if (Delete(h->HubDb->GroupList, g))
	{
		ReleaseGroup(g);
	}

	for (i = 0;i < LIST_NUM(h->HubDb->UserList);i++)
	{
		USER *u = LIST_DATA(h->HubDb->UserList, i);
		Lock(u->lock);
		{
			if (u->Group == g)
			{
				JoinUserToGroup(u, NULL);
			}
		}
		Unlock(u->lock);
	}

	ReleaseGroup(g);

	return true;
}