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
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ USERGROUP ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * GroupName; TYPE_1__* Group; } ;
typedef  TYPE_2__ USER ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseGroup (TYPE_1__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void JoinUserToGroup(USER *u, USERGROUP *g)
{
	// Validate arguments
	if (u == NULL)
	{
		return;
	}

	if (g != NULL)
	{
		// Join
		Lock(u->lock);
		{
			Lock(g->lock);
			{
				if (u->Group != NULL)
				{
					// Remove the user from current group first
					// 
					ReleaseGroup(u->Group);
					u->Group = NULL;
					Free(u->GroupName);
					u->GroupName = NULL;
				}
				// Join the user to the group
				u->GroupName = CopyStr(g->Name);
				u->Group = g;
				AddRef(g->ref);
			}
			Unlock(g->lock);
		}
		Unlock(u->lock);
	}
	else
	{
		// Withdrawal
		Lock(u->lock);
		{
			if (u->Group != NULL)
			{
				// Remove the user from current group
				ReleaseGroup(u->Group);
				u->Group = NULL;
				Free(u->GroupName);
				u->GroupName = NULL;
			}
		}
		Unlock(u->lock);
	}
}