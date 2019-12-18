#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dio {unsigned long refcount; TYPE_1__* iocb; int /*<<< orphan*/  bio_lock; scalar_t__ waiter; } ;
struct bio {struct dio* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  ki_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  dio_bio_complete (struct dio*,struct bio*) ; 
 int /*<<< orphan*/  dio_cache ; 
 int /*<<< orphan*/  dio_complete (struct dio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dio*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void dio_bio_end_aio(struct bio *bio, int error)
{
	struct dio *dio = bio->bi_private;
	unsigned long remaining;
	unsigned long flags;

	/* cleanup the bio */
	dio_bio_complete(dio, bio);

	spin_lock_irqsave(&dio->bio_lock, flags);
	remaining = --dio->refcount;
	if (remaining == 1 && dio->waiter)
		wake_up_process(dio->waiter);
	spin_unlock_irqrestore(&dio->bio_lock, flags);

	if (remaining == 0) {
		dio_complete(dio, dio->iocb->ki_pos, 0, true);
		kmem_cache_free(dio_cache, dio);
	}
}