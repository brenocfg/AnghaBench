#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/ * L3SwList; } ;
struct TYPE_5__ {int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ L3SW ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3DelSw (TYPE_2__*,char*) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void L3FreeAllSw(CEDAR *c)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	o = NewListFast(NULL);

	LockList(c->L3SwList);
	{
		for (i = 0;i < LIST_NUM(c->L3SwList);i++)
		{
			L3SW *s = LIST_DATA(c->L3SwList, i);
			Insert(o, CopyStr(s->Name));
		}

		for (i = 0;i < LIST_NUM(o);i++)
		{
			char *name = LIST_DATA(o, i);

			L3DelSw(c, name);

			Free(name);
		}

		ReleaseList(o);
	}
	UnlockList(c->L3SwList);
}