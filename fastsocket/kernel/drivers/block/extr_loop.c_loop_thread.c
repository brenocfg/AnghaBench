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
struct loop_device {int /*<<< orphan*/  lo_lock; int /*<<< orphan*/  lo_bio_list; int /*<<< orphan*/  lo_event; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ bio_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ kthread_should_stop () ; 
 struct bio* loop_get_bio (struct loop_device*) ; 
 int /*<<< orphan*/  loop_handle_bio (struct loop_device*,struct bio*) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int loop_thread(void *data)
{
	struct loop_device *lo = data;
	struct bio *bio;

	set_user_nice(current, -20);

	while (!kthread_should_stop() || !bio_list_empty(&lo->lo_bio_list)) {

		wait_event_interruptible(lo->lo_event,
				!bio_list_empty(&lo->lo_bio_list) ||
				kthread_should_stop());

		if (bio_list_empty(&lo->lo_bio_list))
			continue;
		spin_lock_irq(&lo->lo_lock);
		bio = loop_get_bio(lo);
		spin_unlock_irq(&lo->lo_lock);

		BUG_ON(!bio);
		loop_handle_bio(lo, bio);
	}

	return 0;
}