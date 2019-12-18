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
struct test_thread_data {int opcode; int* mutexes; size_t opdata; int bkl; void* event; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int MAX_RT_TEST_MUTEXES ; 
#define  RTTEST_LOCK 138 
#define  RTTEST_LOCKBKL 137 
#define  RTTEST_LOCKCONT 136 
#define  RTTEST_LOCKINT 135 
#define  RTTEST_LOCKINTNOWAIT 134 
#define  RTTEST_LOCKNOWAIT 133 
#define  RTTEST_NOP 132 
#define  RTTEST_RESET 131 
#define  RTTEST_RESETEVENT 130 
#define  RTTEST_UNLOCK 129 
#define  RTTEST_UNLOCKBKL 128 
 void* atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/ * mutexes ; 
 int /*<<< orphan*/  rt_mutex_lock (int /*<<< orphan*/ *) ; 
 int rt_mutex_lock_interruptible (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rttest_event ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int handle_op(struct test_thread_data *td, int lockwakeup)
{
	int i, id, ret = -EINVAL;

	switch(td->opcode) {

	case RTTEST_NOP:
		return 0;

	case RTTEST_LOCKCONT:
		td->mutexes[td->opdata] = 1;
		td->event = atomic_add_return(1, &rttest_event);
		return 0;

	case RTTEST_RESET:
		for (i = 0; i < MAX_RT_TEST_MUTEXES; i++) {
			if (td->mutexes[i] == 4) {
				rt_mutex_unlock(&mutexes[i]);
				td->mutexes[i] = 0;
			}
		}

		if (!lockwakeup && td->bkl == 4) {
			unlock_kernel();
			td->bkl = 0;
		}
		return 0;

	case RTTEST_RESETEVENT:
		atomic_set(&rttest_event, 0);
		return 0;

	default:
		if (lockwakeup)
			return ret;
	}

	switch(td->opcode) {

	case RTTEST_LOCK:
	case RTTEST_LOCKNOWAIT:
		id = td->opdata;
		if (id < 0 || id >= MAX_RT_TEST_MUTEXES)
			return ret;

		td->mutexes[id] = 1;
		td->event = atomic_add_return(1, &rttest_event);
		rt_mutex_lock(&mutexes[id]);
		td->event = atomic_add_return(1, &rttest_event);
		td->mutexes[id] = 4;
		return 0;

	case RTTEST_LOCKINT:
	case RTTEST_LOCKINTNOWAIT:
		id = td->opdata;
		if (id < 0 || id >= MAX_RT_TEST_MUTEXES)
			return ret;

		td->mutexes[id] = 1;
		td->event = atomic_add_return(1, &rttest_event);
		ret = rt_mutex_lock_interruptible(&mutexes[id], 0);
		td->event = atomic_add_return(1, &rttest_event);
		td->mutexes[id] = ret ? 0 : 4;
		return ret ? -EINTR : 0;

	case RTTEST_UNLOCK:
		id = td->opdata;
		if (id < 0 || id >= MAX_RT_TEST_MUTEXES || td->mutexes[id] != 4)
			return ret;

		td->event = atomic_add_return(1, &rttest_event);
		rt_mutex_unlock(&mutexes[id]);
		td->event = atomic_add_return(1, &rttest_event);
		td->mutexes[id] = 0;
		return 0;

	case RTTEST_LOCKBKL:
		if (td->bkl)
			return 0;
		td->bkl = 1;
		lock_kernel();
		td->bkl = 4;
		return 0;

	case RTTEST_UNLOCKBKL:
		if (td->bkl != 4)
			break;
		unlock_kernel();
		td->bkl = 0;
		return 0;

	default:
		break;
	}
	return ret;
}