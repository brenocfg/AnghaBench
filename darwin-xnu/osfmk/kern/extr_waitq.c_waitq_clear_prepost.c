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
struct waitq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  waitq_clear_prepost_locked (struct waitq*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int waitq_valid (struct waitq*) ; 

void waitq_clear_prepost(struct waitq *waitq)
{
	assert(waitq_valid(waitq));
	assert(!waitq_irq_safe(waitq));

	waitq_lock(waitq);
	/* it doesn't matter to us if the lock is dropped here */
	(void)waitq_clear_prepost_locked(waitq);
	waitq_unlock(waitq);
}