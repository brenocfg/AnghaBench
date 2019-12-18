#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 scalar_t__ Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadList ; 

void DelWaitThread(THREAD *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	LockList(WaitThreadList);
	{
		if (Delete(WaitThreadList, t))
		{
			ReleaseThread(t);
		}
	}
	UnlockList(WaitThreadList);
}