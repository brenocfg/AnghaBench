#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ct1 ;
typedef  int /*<<< orphan*/  c ;
typedef  int UINT ;
struct TYPE_9__ {int num; int a; int /*<<< orphan*/  lock; int /*<<< orphan*/ * wait_thread; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ EVENT ;
typedef  TYPE_1__ CHECK_THREAD_3 ;
typedef  TYPE_1__ CHECK_THREAD_1 ;

/* Variables and functions */
 int CHECK_THREAD_INCREMENT_COUNT ; 
 int /*<<< orphan*/  CheckThread1 ; 
 int /*<<< orphan*/  CheckThread2 ; 
 int /*<<< orphan*/  CheckThread3 ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_1__* NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Print (char*,int,...) ; 
 int /*<<< orphan*/  ReleaseEvent (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set (TYPE_1__*) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ ** ZeroMalloc (int) ; 

bool CheckThread()
{
	bool ok = true;
	CHECK_THREAD_1 ct1;
	UINT num = 32;
	UINT i;
	THREAD **threads;
	EVENT *e;
	THREAD *t2;
	THREAD *t;
	CHECK_THREAD_3 c;

	e = NewEvent();

	Zero(&ct1, sizeof(ct1));
	ct1.lock = NewLock();

	t2 = NewThread(CheckThread2, e);
	ct1.wait_thread = t2;

	threads = ZeroMalloc(sizeof(THREAD *) * num);
	for (i = 0;i < num;i++)
	{
		threads[i] = NewThread(CheckThread1, &ct1);
		if (threads[i] == NULL)
		{
			Print("Thread %u Create Failed.\n", i);
			ok = false;
		}
	}

	Set(e);

	for (i = 0;i < num;i++)
	{
		WaitThread(threads[i], INFINITE);
		ReleaseThread(threads[i]);
	}

	Free(threads);

	if (ct1.num != (num * CHECK_THREAD_INCREMENT_COUNT))
	{
		Print("Threading: %u != %u\n", ct1.num, num * CHECK_THREAD_INCREMENT_COUNT);
		ok = false;
	}

	DeleteLock(ct1.lock);

	WaitThread(t2, INFINITE);
	ReleaseThread(t2);

	ReleaseEvent(e);

	num = 32;

	Zero(&c, sizeof(c));
	c.num = num;
	t = NewThread(CheckThread3, &c);
	WaitThread(t, INFINITE);
	ReleaseThread(t);

	if (c.a != num)
	{
		Print("Threading: %u != %u\n", c.a, num);
		ok = false;
	}

	return ok;
}