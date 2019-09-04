#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
struct TYPE_7__ {scalar_t__ Param1; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAllUserListCache (TYPE_1__*) ; 
 int IsUserMatchInUserList (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  LockList (TYPE_1__*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (TYPE_1__*) ; 

bool IsUserMatchInUserListWithCacheExpires(LIST *o, char *filename, UINT64 user_hash, UINT64 lifetime)
{
	bool ret = false;
	UINT64 now = Tick64();
	// Validate arguments
	if (o == NULL || filename == NULL || user_hash == 0)
	{
		return false;
	}

	LockList(o);
	{
		if (lifetime != 0)
		{
			if (o->Param1 == 0 || (now >= (o->Param1 + lifetime)))
			{
				DeleteAllUserListCache(o);

				o->Param1 = now;
			}
		}

		ret = IsUserMatchInUserList(o, filename, user_hash);
	}
	UnlockList(o);

	return ret;
}