#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/  ListenerList; } ;
typedef  int /*<<< orphan*/  LISTENER ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseListener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopListener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void StopAllListener(CEDAR *c)
{
	LISTENER **array;
	UINT i, num;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	LockList(c->ListenerList);
	{
		array = ToArray(c->ListenerList);
		num = LIST_NUM(c->ListenerList);
		DeleteAll(c->ListenerList);
	}
	UnlockList(c->ListenerList);

	for (i = 0;i < num;i++)
	{
		StopListener(array[i]);
		ReleaseListener(array[i]);
	}
	Free(array);
}