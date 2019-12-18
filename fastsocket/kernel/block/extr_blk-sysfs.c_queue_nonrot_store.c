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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  queue_var_store (unsigned long*,char const*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t queue_nonrot_store(struct request_queue *q, const char *page,
				  size_t count)
{
	unsigned long nm;
	ssize_t ret = queue_var_store(&nm, page, count);

	spin_lock_irq(q->queue_lock);
	if (nm)
		queue_flag_clear(QUEUE_FLAG_NONROT, q);
	else
		queue_flag_set(QUEUE_FLAG_NONROT, q);
	spin_unlock_irq(q->queue_lock);

	return ret;
}