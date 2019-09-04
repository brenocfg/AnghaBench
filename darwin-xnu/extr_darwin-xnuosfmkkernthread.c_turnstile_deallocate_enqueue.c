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
struct turnstile {int /*<<< orphan*/  ts_deallocate_link; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_terminate_lock ; 
 int /*<<< orphan*/  thread_terminate_queue ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_deallocate_queue ; 

void
turnstile_deallocate_enqueue(
	struct turnstile *turnstile)
{
	spl_t s = splsched();

	simple_lock(&thread_terminate_lock);
	enqueue_tail(&turnstile_deallocate_queue, &turnstile->ts_deallocate_link);
	simple_unlock(&thread_terminate_lock);

	thread_wakeup((event_t)&thread_terminate_queue);
	splx(s);
}