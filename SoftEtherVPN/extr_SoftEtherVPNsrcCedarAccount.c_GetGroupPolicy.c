#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * Policy; } ;
typedef  TYPE_1__ USERGROUP ;
typedef  int /*<<< orphan*/  POLICY ;

/* Variables and functions */
 int /*<<< orphan*/ * ClonePolicy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

POLICY *GetGroupPolicy(USERGROUP *g)
{
	POLICY *ret;
	// Validate arguments
	if (g == NULL)
	{
		return NULL;
	}

	Lock(g->lock);
	{
		if (g->Policy == NULL)
		{
			ret = NULL;
		}
		else
		{
			ret = ClonePolicy(g->Policy);
		}
	}
	Unlock(g->lock);

	return ret;
}