#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct blkfront_info {TYPE_1__* gd; int /*<<< orphan*/ * rq; int /*<<< orphan*/  callback; } ;
struct TYPE_3__ {unsigned int first_minor; unsigned int minors; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_stop_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkif_io_lock ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  gnttab_cancel_free_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xlbd_release_minors (unsigned int,unsigned int) ; 

__attribute__((used)) static void xlvbd_release_gendisk(struct blkfront_info *info)
{
	unsigned int minor, nr_minors;
	unsigned long flags;

	if (info->rq == NULL)
		return;

	spin_lock_irqsave(&blkif_io_lock, flags);

	/* No more blkif_request(). */
	blk_stop_queue(info->rq);

	/* No more gnttab callback work. */
	gnttab_cancel_free_callback(&info->callback);
	spin_unlock_irqrestore(&blkif_io_lock, flags);

	/* Flush gnttab callback work. Must be done with no locks held. */
	flush_scheduled_work();

	del_gendisk(info->gd);

	minor = info->gd->first_minor;
	nr_minors = info->gd->minors;
	xlbd_release_minors(minor, nr_minors);

	blk_cleanup_queue(info->rq);
	info->rq = NULL;

	put_disk(info->gd);
	info->gd = NULL;
}