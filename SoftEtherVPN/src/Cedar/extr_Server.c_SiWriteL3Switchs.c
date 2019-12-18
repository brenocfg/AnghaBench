#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  L3SwList; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Name; } ;
struct TYPE_7__ {TYPE_3__* Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ L3SW ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteL3SwitchCfg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SiWriteL3Switchs(FOLDER *f, SERVER *s)
{
	UINT i;
	FOLDER *folder;
	CEDAR *c;
	// Validate arguments
	if (f == NULL || s == NULL)
	{
		return;
	}
	c = s->Cedar;

	LockList(c->L3SwList);
	{
		for (i = 0;i < LIST_NUM(c->L3SwList);i++)
		{
			L3SW *sw = LIST_DATA(c->L3SwList, i);

			Lock(sw->lock);
			{
				folder = CfgCreateFolder(f, sw->Name);

				SiWriteL3SwitchCfg(folder, sw);
			}
			Unlock(sw->lock);
		}
	}
	UnlockList(c->L3SwList);
}