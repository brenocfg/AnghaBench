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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int Ready; int /*<<< orphan*/  lock; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ COUNTER ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT Count(COUNTER *c)
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
		ret = c->c;
	}
	Unlock(c->lock);

	return ret;
}