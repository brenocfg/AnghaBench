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
struct TYPE_3__ {int /*<<< orphan*/  Listener; int /*<<< orphan*/  AdminThreadList; int /*<<< orphan*/  AdminSockList; int /*<<< orphan*/  Cedar; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INFINITE ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseListener (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopAllListener (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ElStopListener(EL *e)
{
	UINT i;
	THREAD **threads;
	SOCK **socks;
	UINT num_threads, num_socks;
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	StopAllListener(e->Cedar);

	LockList(e->AdminThreadList);
	{
		threads = ToArray(e->AdminThreadList);
		num_threads = LIST_NUM(e->AdminThreadList);
		DeleteAll(e->AdminThreadList);

		socks = ToArray(e->AdminSockList);
		num_socks = LIST_NUM(e->AdminSockList);
		DeleteAll(e->AdminSockList);
	}
	UnlockList(e->AdminThreadList);

	for (i = 0;i < num_socks;i++)
	{
		Disconnect(socks[i]);
		ReleaseSock(socks[i]);
	}

	for (i = 0;i < num_threads;i++)
	{
		WaitThread(threads[i], INFINITE);
		ReleaseThread(threads[i]);
	}

	Free(threads);
	Free(socks);

	ReleaseList(e->AdminSockList);
	ReleaseList(e->AdminThreadList);

	ReleaseListener(e->Listener);
}