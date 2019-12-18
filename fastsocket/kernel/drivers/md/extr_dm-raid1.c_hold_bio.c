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
struct mirror_set {int /*<<< orphan*/  lock; int /*<<< orphan*/  holds; int /*<<< orphan*/  ti; int /*<<< orphan*/  suspend; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ENDIO_REQUEUE ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ dm_noflush_suspending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hold_bio(struct mirror_set *ms, struct bio *bio)
{
	/*
	 * Lock is required to avoid race condition during suspend
	 * process.
	 */
	spin_lock_irq(&ms->lock);

	if (atomic_read(&ms->suspend)) {
		spin_unlock_irq(&ms->lock);

		/*
		 * If device is suspended, complete the bio.
		 */
		if (dm_noflush_suspending(ms->ti))
			bio_endio(bio, DM_ENDIO_REQUEUE);
		else
			bio_endio(bio, -EIO);
		return;
	}

	/*
	 * Hold bio until the suspend is complete.
	 */
	bio_list_add(&ms->holds, bio);
	spin_unlock_irq(&ms->lock);
}