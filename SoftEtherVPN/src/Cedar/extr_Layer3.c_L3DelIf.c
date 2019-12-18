#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Active; int /*<<< orphan*/  lock; int /*<<< orphan*/  IfList; } ;
typedef  TYPE_1__ L3SW ;
typedef  int /*<<< orphan*/  L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * L3SearchIf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

bool L3DelIf(L3SW *s, char *hubname)
{
	L3IF *f;
	bool ret = false;
	// Validate arguments
	if (s == NULL || hubname == NULL)
	{
		return false;
	}

	Lock(s->lock);
	{
		if (s->Active == false)
		{
			f = L3SearchIf(s, hubname);

			if (f != NULL)
			{
				// Remove
				Delete(s->IfList, f);
				Free(f);

				ret = true;
			}
		}
	}
	Unlock(s->lock);

	return ret;
}