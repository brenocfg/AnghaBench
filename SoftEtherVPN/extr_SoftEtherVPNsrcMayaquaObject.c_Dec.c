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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int Ready; scalar_t__ c; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ COUNTER ;

/* Variables and functions */
 int /*<<< orphan*/  KS_CURRENT_COUNT ; 
 int /*<<< orphan*/  KS_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_DEC_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT Dec(COUNTER *c)
{
	UINT ret;
	// Validate arguments
	if (c == NULL)
	{
		return 0;
	}
	if (c->Ready == false)
	{
		return 0;
	}

	Lock(c->lock);
	{
		if (c->c != 0)
		{
			c->c--;
			ret = c->c;
		}
		else
		{
			ret = 0;
		}
	}
	Unlock(c->lock);

	// KS
	KS_INC(KS_DEC_COUNT);
	KS_DEC(KS_CURRENT_COUNT);

	return ret;
}