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
struct dio {int refcount; int /*<<< orphan*/  bio_lock; struct bio* bio_list; int /*<<< orphan*/ * waiter; } ;
struct bio {struct bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct bio *dio_await_one(struct dio *dio)
{
	unsigned long flags;
	struct bio *bio = NULL;

	spin_lock_irqsave(&dio->bio_lock, flags);

	/*
	 * Wait as long as the list is empty and there are bios in flight.  bio
	 * completion drops the count, maybe adds to the list, and wakes while
	 * holding the bio_lock so we don't need set_current_state()'s barrier
	 * and can call it after testing our condition.
	 */
	while (dio->refcount > 1 && dio->bio_list == NULL) {
		__set_current_state(TASK_UNINTERRUPTIBLE);
		dio->waiter = current;
		spin_unlock_irqrestore(&dio->bio_lock, flags);
		io_schedule();
		/* wake up sets us TASK_RUNNING */
		spin_lock_irqsave(&dio->bio_lock, flags);
		dio->waiter = NULL;
	}
	if (dio->bio_list) {
		bio = dio->bio_list;
		dio->bio_list = bio->bi_private;
	}
	spin_unlock_irqrestore(&dio->bio_lock, flags);
	return bio;
}