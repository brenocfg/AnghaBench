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
struct TYPE_4__ {int /*<<< orphan*/  UserHashList; } ;
typedef  TYPE_1__ USERLIST ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 TYPE_1__* FindUserList (int /*<<< orphan*/ *,char*) ; 
 int IsInt64InList (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* LoadUserList (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

bool IsUserMatchInUserList(LIST *o, char *filename, UINT64 user_hash)
{
	USERLIST *u;
	bool ret = false;
	// Validate arguments
	if (o == NULL || filename == NULL || user_hash == 0)
	{
		return false;
	}

	LockList(o);
	{
		u = FindUserList(o, filename);
		if (u == NULL)
		{
			u = LoadUserList(o, filename);
		}

		if (u != NULL)
		{
			ret = IsInt64InList(u->UserHashList, user_hash);
		}
	}
	UnlockList(o);

	return ret;
}