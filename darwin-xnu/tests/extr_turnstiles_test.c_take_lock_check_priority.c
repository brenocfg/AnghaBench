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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_EQ (int,int,char*,int /*<<< orphan*/ ,int) ; 
 int get_pri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_thread_self () ; 
 int /*<<< orphan*/  pthread_threadid_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  turnstile_prim_lock (int) ; 
 int /*<<< orphan*/  turnstile_prim_unlock (int) ; 

__attribute__((used)) static void *
take_lock_check_priority(void * arg)
{
	int old_pri = get_pri(mach_thread_self());
	int unboosted_pri;
	int boosted_pri;
	int after_unlock_pri;
	uint64_t tid;
	int type = (int)arg;

	pthread_threadid_np(NULL, &tid);

	T_ASSERT_EQ(old_pri, 37, "thread(%llu) priority before acquiring the lock is %d\n", tid, old_pri);

	/* Take the test lock */
	turnstile_prim_lock(type);

	unboosted_pri =  get_pri(mach_thread_self());
	T_ASSERT_EQ(unboosted_pri, 37, "thread(%llu) priority after acquiring the lock (uncontended) is %d\n", tid, unboosted_pri);

	sleep(8);

	/* Check for elevated priority */
	boosted_pri =  get_pri(mach_thread_self());
	T_ASSERT_EQ(boosted_pri, 47, "thread(%llu) priority after contention by 47 thread is %d\n", tid, boosted_pri);

	/* Drop the lock */
	turnstile_prim_unlock(type);

	/* Check for regular priority */
	after_unlock_pri =  get_pri(mach_thread_self());
	T_ASSERT_EQ(after_unlock_pri, 37, "thread(%llu) priority after dropping lock is %d\n", tid, after_unlock_pri);

	return NULL;
}