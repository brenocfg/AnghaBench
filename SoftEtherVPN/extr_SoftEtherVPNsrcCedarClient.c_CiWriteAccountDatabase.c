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
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  AccountList; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CiWriteAccountData (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiWriteAccountDatabase(CLIENT *c, FOLDER *f)
{
	char name[MAX_SIZE];
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	LockList(c->AccountList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(c->AccountList);i++)
		{
			ACCOUNT *a = LIST_DATA(c->AccountList, i);

			{
				Format(name, sizeof(name), "Account%u", i);
				Lock(a->lock);
				{
					CiWriteAccountData(CfgCreateFolder(f, name), a);
				}
				Unlock(a->lock);
			}
		}
	}
	UnlockList(c->AccountList);
}