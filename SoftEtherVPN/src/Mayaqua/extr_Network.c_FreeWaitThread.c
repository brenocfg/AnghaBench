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
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INFINITE ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WaitThreadList ; 

void FreeWaitThread()
{
	UINT i, num;
	THREAD **threads;

	LockList(WaitThreadList);
	{
		num = LIST_NUM(WaitThreadList);
		threads = ToArray(WaitThreadList);
		DeleteAll(WaitThreadList);
	}
	UnlockList(WaitThreadList);

	for (i = 0;i < num;i++)
	{
		THREAD *t = threads[i];
		WaitThread(t, INFINITE);
		ReleaseThread(t);
	}

	Free(threads);

	ReleaseList(WaitThreadList);
	WaitThreadList = NULL;
}