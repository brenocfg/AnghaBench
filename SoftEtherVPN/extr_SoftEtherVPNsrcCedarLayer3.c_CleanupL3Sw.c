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
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  TableList; int /*<<< orphan*/  IfList; } ;
typedef  TYPE_1__ L3TABLE ;
typedef  TYPE_1__ L3SW ;
typedef  TYPE_1__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void CleanupL3Sw(L3SW *s)
{
	UINT i;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(s->IfList);i++)
	{
		L3IF *f = LIST_DATA(s->IfList, i);
		Free(f);
	}
	ReleaseList(s->IfList);

	for (i = 0;i < LIST_NUM(s->TableList);i++)
	{
		L3TABLE *t = LIST_DATA(s->TableList, i);
		Free(t);
	}
	ReleaseList(s->TableList);

	DeleteLock(s->lock);
	Free(s);
}