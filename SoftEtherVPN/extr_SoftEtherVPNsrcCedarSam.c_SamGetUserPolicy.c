#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * Policy; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ USERGROUP ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_1__* Group; int /*<<< orphan*/ * Policy; } ;
typedef  TYPE_2__ USER ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 TYPE_2__* AcGetUser (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ClonePolicy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseGroup (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_2__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

POLICY *SamGetUserPolicy(HUB *h, char *username)
{
	POLICY *ret = NULL;
	// Validate arguments
	if (h == NULL || username == NULL)
	{
		return NULL;
	}

	AcLock(h);
	{
		USER *u;
		u = AcGetUser(h, username);
		if (u)
		{
			USERGROUP *g = NULL;
			Lock(u->lock);
			{
				if (u->Policy != NULL)
				{
					ret = ClonePolicy(u->Policy);
				}

				g = u->Group;

				if (g != NULL)
				{
					AddRef(g->ref);
				}
			}
			Unlock(u->lock);

			ReleaseUser(u);
			u = NULL;

			if (ret == NULL)
			{
				if (g != NULL)
				{
					Lock(g->lock);
					{
						ret = ClonePolicy(g->Policy);
					}
					Unlock(g->lock);
				}
			}

			if (g != NULL)
			{
				ReleaseGroup(g);
			}
		}
	}
	AcUnlock(h);

	return ret;
}