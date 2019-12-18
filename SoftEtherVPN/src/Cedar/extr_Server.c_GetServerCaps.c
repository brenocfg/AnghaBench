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
struct TYPE_4__ {int /*<<< orphan*/  CapsCacheLock; int /*<<< orphan*/ * CapsListCache; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  CAPSLIST ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetServerCapsMain (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void GetServerCaps(SERVER *s, CAPSLIST *t)
{
	// Validate arguments
	if (s == NULL || t == NULL)
	{
		return;
	}

	Lock(s->CapsCacheLock);
	{

		if (s->CapsListCache == NULL)
		{
			s->CapsListCache = ZeroMalloc(sizeof(CAPSLIST));
			GetServerCapsMain(s, s->CapsListCache);
		}

		Copy(t, s->CapsListCache, sizeof(CAPSLIST));
	}
	Unlock(s->CapsCacheLock);
}