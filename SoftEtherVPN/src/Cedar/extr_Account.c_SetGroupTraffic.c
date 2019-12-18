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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Traffic; } ;
typedef  TYPE_1__ USERGROUP ;
typedef  int /*<<< orphan*/  TRAFFIC ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ ,int) ; 

void SetGroupTraffic(USERGROUP *g, TRAFFIC *t)
{
	// Validate arguments
	if (g == NULL)
	{
		return;
	}

	Lock(g->lock);
	{
		if (t != NULL)
		{
			Copy(g->Traffic, t, sizeof(TRAFFIC));
		}
		else
		{
			Zero(g->Traffic, sizeof(TRAFFIC));
		}
	}
	Unlock(g->lock);
}