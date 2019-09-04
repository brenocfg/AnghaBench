#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  TYPE_2__* thread_call_t ;
typedef  int /*<<< orphan*/  thread_call_data_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  q_link; } ;
struct TYPE_5__ {TYPE_1__ tc_call; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_PREEMPT_HIGH ; 
 int /*<<< orphan*/  FALSE ; 
 size_t INTERNAL_CALL_COUNT ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int SYNC_POLICY_DISABLE_IRQ ; 
 int SYNC_POLICY_FIFO ; 
 int /*<<< orphan*/  THREAD_CALL_DEALLOC_INTERVAL_NS ; 
 size_t THREAD_CALL_INDEX_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Z_CALLERACCT ; 
 int /*<<< orphan*/  Z_NOENCRYPT ; 
 int /*<<< orphan*/  daemon_waitq ; 
 int /*<<< orphan*/  disable_ints_and_lock () ; 
 int /*<<< orphan*/  enable_ints_and_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* internal_call_storage ; 
 scalar_t__ kernel_thread_start_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanotime_to_absolutetime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_call_daemon ; 
 int /*<<< orphan*/  thread_call_daemon_awake ; 
 int /*<<< orphan*/  thread_call_dealloc_interval_abs ; 
 int /*<<< orphan*/  thread_call_group_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * thread_call_groups ; 
 int /*<<< orphan*/  thread_call_internal_queue ; 
 int /*<<< orphan*/  thread_call_internal_queue_count ; 
 int /*<<< orphan*/  thread_call_lck_grp ; 
 int /*<<< orphan*/  thread_call_lock_data ; 
 int /*<<< orphan*/  thread_call_zone ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zinit (int,int,int,char*) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
thread_call_initialize(void)
{
	int tc_size = sizeof (thread_call_data_t);
	thread_call_zone = zinit(tc_size, 4096 * tc_size, 16 * tc_size, "thread_call");
	zone_change(thread_call_zone, Z_CALLERACCT, FALSE);
	zone_change(thread_call_zone, Z_NOENCRYPT, TRUE);

	lck_grp_init(&thread_call_lck_grp, "thread_call", LCK_GRP_ATTR_NULL);
	lck_mtx_init(&thread_call_lock_data, &thread_call_lck_grp, LCK_ATTR_NULL);

	nanotime_to_absolutetime(0, THREAD_CALL_DEALLOC_INTERVAL_NS, &thread_call_dealloc_interval_abs);
	waitq_init(&daemon_waitq, SYNC_POLICY_DISABLE_IRQ | SYNC_POLICY_FIFO);

	for (uint32_t i = 0; i < THREAD_CALL_INDEX_MAX; i++)
		thread_call_group_setup(&thread_call_groups[i]);

	spl_t s = disable_ints_and_lock();

	queue_init(&thread_call_internal_queue);
	for (
			thread_call_t call = internal_call_storage;
			call < &internal_call_storage[INTERNAL_CALL_COUNT];
			call++) {

		enqueue_tail(&thread_call_internal_queue, &call->tc_call.q_link);
		thread_call_internal_queue_count++;
	}

	thread_call_daemon_awake = TRUE;

	enable_ints_and_unlock(s);

	thread_t thread;
	kern_return_t result;

	result = kernel_thread_start_priority((thread_continue_t)thread_call_daemon,
	                                      NULL, BASEPRI_PREEMPT_HIGH + 1, &thread);
	if (result != KERN_SUCCESS)
		panic("thread_call_initialize");

	thread_deallocate(thread);
}