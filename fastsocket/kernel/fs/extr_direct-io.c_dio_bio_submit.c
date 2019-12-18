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
struct dio_submit {int /*<<< orphan*/  logical_offset_in_bio; scalar_t__ boundary; struct bio* bio; int /*<<< orphan*/  (* submit_io ) (scalar_t__,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dio {scalar_t__ rw; int /*<<< orphan*/  inode; scalar_t__ is_async; int /*<<< orphan*/  bio_lock; int /*<<< orphan*/  refcount; } ;
struct bio {struct dio* bi_private; } ;

/* Variables and functions */
 scalar_t__ READ ; 
 int /*<<< orphan*/  bio_set_pages_dirty (struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio (scalar_t__,struct bio*) ; 

__attribute__((used)) static inline void dio_bio_submit(struct dio *dio, struct dio_submit *sdio)
{
	struct bio *bio = sdio->bio;
	unsigned long flags;

	bio->bi_private = dio;

	spin_lock_irqsave(&dio->bio_lock, flags);
	dio->refcount++;
	spin_unlock_irqrestore(&dio->bio_lock, flags);

	if (dio->is_async && dio->rw == READ)
		bio_set_pages_dirty(bio);

	if (sdio->submit_io)
		sdio->submit_io(dio->rw, bio, dio->inode,
			       sdio->logical_offset_in_bio);
	else
		submit_bio(dio->rw, bio);

	sdio->bio = NULL;
	sdio->boundary = 0;
	sdio->logical_offset_in_bio = 0;
}