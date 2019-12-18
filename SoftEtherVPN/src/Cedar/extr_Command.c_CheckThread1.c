#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ num; int /*<<< orphan*/  wait_thread; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ CHECK_THREAD_1 ;

/* Variables and functions */
 scalar_t__ CHECK_THREAD_INCREMENT_COUNT ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  InputToNull (void*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ RetZero () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_thread_global_1 ; 

void CheckThread1(THREAD *thread, void *param)
{
	CHECK_THREAD_1 *ct1 = (CHECK_THREAD_1 *)param;
	UINT i;
	UINT num = CHECK_THREAD_INCREMENT_COUNT;

	WaitThread(ct1->wait_thread, INFINITE);

	for (i = 0;i < num;i++)
	{
		Lock(ct1->lock);
		check_thread_global_1 = ct1->num;
		InputToNull((void *)check_thread_global_1);
		check_thread_global_1 = check_thread_global_1 + 1 + RetZero();
		ct1->num = check_thread_global_1;
		Unlock(ct1->lock);
	}
}