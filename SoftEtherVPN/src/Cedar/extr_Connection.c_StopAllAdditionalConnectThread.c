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
struct TYPE_3__ {int ServerMode; int /*<<< orphan*/  ConnectingThreads; int /*<<< orphan*/  ConnectingSocks; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,size_t) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INFINITE ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void StopAllAdditionalConnectThread(CONNECTION *c)
{
	UINT i, num;
	SOCK **socks;
	THREAD **threads;
	// Validate arguments
	if (c == NULL || c->ServerMode != false)
	{
		return;
	}

	// Disconnect the socket first
	LockList(c->ConnectingSocks);
	{
		num = LIST_NUM(c->ConnectingSocks);
		socks = ToArray(c->ConnectingSocks);
		DeleteAll(c->ConnectingSocks);
	}
	UnlockList(c->ConnectingSocks);
	for (i = 0;i < num;i++)
	{
		Disconnect(socks[i]);
		ReleaseSock(socks[i]);
	}
	Free(socks);

	// Then, wait for the suspension of the thread
	LockList(c->ConnectingThreads);
	{
		num = LIST_NUM(c->ConnectingThreads);
		Debug("c->ConnectingThreads: %u\n", num);
		threads = ToArray(c->ConnectingThreads);
		DeleteAll(c->ConnectingThreads);
	}
	UnlockList(c->ConnectingThreads);
	for (i = 0;i < num;i++)
	{
		WaitThread(threads[i], INFINITE);
		ReleaseThread(threads[i]);
	}
	Free(threads);
}