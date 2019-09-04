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
struct TYPE_4__ {scalar_t__ AuthType; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ USER ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 scalar_t__ AUTHTYPE_ANONYMOUS ; 
 TYPE_1__* AcGetUser (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_1__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

bool SamAuthUserByAnonymous(HUB *h, char *username)
{
	bool b = false;
	// Validate arguments
	if (h == NULL || username == NULL)
	{
		return false;
	}

	AcLock(h);
	{
		USER *u = AcGetUser(h, username);
		if (u)
		{
			Lock(u->lock);
			{
				if (u->AuthType == AUTHTYPE_ANONYMOUS)
				{
					b = true;
				}
			}
			Unlock(u->lock);
		}
		ReleaseUser(u);
	}
	AcUnlock(h);

	return b;
}