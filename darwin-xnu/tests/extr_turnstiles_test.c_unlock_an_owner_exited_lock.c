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
 int /*<<< orphan*/  turnstile_prim_unlock (int) ; 

__attribute__((used)) static void *
unlock_an_owner_exited_lock(void *arg)
{
	uint64_t tid;
	int type = (int)arg;

	pthread_threadid_np(NULL, &tid);
	sleep(12);

	int old_pri = get_pri(mach_thread_self());
	T_ASSERT_EQ(old_pri, 47, "thread(%llu) priority before acquiring the lock is %d\n", tid, old_pri);

	/* Unlock the test lock causing the turnstile code to call thread_deallocate_safe */
	turnstile_prim_unlock(type);
	return NULL;
}