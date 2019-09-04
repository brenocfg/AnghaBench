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
struct TYPE_4__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ USER ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiWriteUserCfg (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void SiWriteUserList(FOLDER *f, LIST *o)
{
	// Validate arguments
	if (f == NULL || o == NULL)
	{
		return;
	}

	LockList(o);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(o);i++)
		{
			USER *u = LIST_DATA(o, i);
			SiWriteUserCfg(CfgCreateFolder(f, u->Name), u);
		}
	}
	UnlockList(o);
}