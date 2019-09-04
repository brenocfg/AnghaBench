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
typedef  int /*<<< orphan*/  wait_timeout_urgency_t ;
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  int /*<<< orphan*/  wait_interrupt_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  event64_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  panic (char*,struct waitq*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_assert_wait64_locked (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 

wait_result_t waitq_assert_wait64_leeway(struct waitq *waitq,
					 event64_t wait_event,
					 wait_interrupt_t interruptible,
					 wait_timeout_urgency_t urgency,
					 uint64_t deadline,
					 uint64_t leeway)
{
	wait_result_t ret;
	thread_t thread = current_thread();
	spl_t s;

	if (!waitq_valid(waitq))
		panic("Invalid waitq: %p", waitq);

	if (waitq_irq_safe(waitq))
		s = splsched();

	waitq_lock(waitq);
	ret = waitq_assert_wait64_locked(waitq, wait_event, interruptible,
					 urgency, deadline, leeway, thread);
	waitq_unlock(waitq);

	if (waitq_irq_safe(waitq))
		splx(s);

	return ret;
}