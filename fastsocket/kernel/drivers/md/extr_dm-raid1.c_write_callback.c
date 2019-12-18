#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  head; } ;
struct mirror_set {unsigned int nr_mirrors; int /*<<< orphan*/  lock; TYPE_1__ failures; scalar_t__ mirror; } ;
struct bio {int dummy; } ;
struct TYPE_4__ {struct mirror_set* ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RAID1_WRITE_ERROR ; 
 int /*<<< orphan*/  bio_endio (struct bio*,unsigned int) ; 
 TYPE_2__* bio_get_m (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (TYPE_1__*,struct bio*) ; 
 int /*<<< orphan*/  bio_set_m (struct bio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_mirror (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  wakeup_mirrord (struct mirror_set*) ; 

__attribute__((used)) static void write_callback(unsigned long error, void *context)
{
	unsigned i, ret = 0;
	struct bio *bio = (struct bio *) context;
	struct mirror_set *ms;
	int should_wake = 0;
	unsigned long flags;

	ms = bio_get_m(bio)->ms;
	bio_set_m(bio, NULL);

	/*
	 * NOTE: We don't decrement the pending count here,
	 * instead it is done by the targets endio function.
	 * This way we handle both writes to SYNC and NOSYNC
	 * regions with the same code.
	 */
	if (likely(!error)) {
		bio_endio(bio, ret);
		return;
	}

	for (i = 0; i < ms->nr_mirrors; i++)
		if (test_bit(i, &error))
			fail_mirror(ms->mirror + i, DM_RAID1_WRITE_ERROR);

	/*
	 * Need to raise event.  Since raising
	 * events can block, we need to do it in
	 * the main thread.
	 */
	spin_lock_irqsave(&ms->lock, flags);
	if (!ms->failures.head)
		should_wake = 1;
	bio_list_add(&ms->failures, bio);
	spin_unlock_irqrestore(&ms->lock, flags);
	if (should_wake)
		wakeup_mirrord(ms);
}