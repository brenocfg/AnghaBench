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
struct request_queue {struct loop_device* queuedata; } ;
struct loop_device {scalar_t__ lo_state; int lo_flags; int /*<<< orphan*/  lo_lock; int /*<<< orphan*/  lo_event; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int LO_FLAGS_READ_ONLY ; 
 scalar_t__ Lo_bound ; 
 int READ ; 
 int READA ; 
 int WRITE ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int bio_rw (struct bio*) ; 
 int /*<<< orphan*/  loop_add_bio (struct loop_device*,struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loop_make_request(struct request_queue *q, struct bio *old_bio)
{
	struct loop_device *lo = q->queuedata;
	int rw = bio_rw(old_bio);

	if (rw == READA)
		rw = READ;

	BUG_ON(!lo || (rw != READ && rw != WRITE));

	spin_lock_irq(&lo->lo_lock);
	if (lo->lo_state != Lo_bound)
		goto out;
	if (unlikely(rw == WRITE && (lo->lo_flags & LO_FLAGS_READ_ONLY)))
		goto out;
	loop_add_bio(lo, old_bio);
	wake_up(&lo->lo_event);
	spin_unlock_irq(&lo->lo_lock);
	return 0;

out:
	spin_unlock_irq(&lo->lo_lock);
	bio_io_error(old_bio);
	return 0;
}