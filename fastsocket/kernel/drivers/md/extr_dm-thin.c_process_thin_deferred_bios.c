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
struct bio_list {int dummy; } ;
struct thin_c {int /*<<< orphan*/  lock; struct bio_list deferred_bio_list; scalar_t__ requeue_mode; struct pool* pool; } ;
struct pool {int /*<<< orphan*/  (* process_bio ) (struct thin_c*,struct bio*) ;int /*<<< orphan*/  (* process_discard ) (struct thin_c*,struct bio*) ;} ;
struct bio {int bi_rw; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int /*<<< orphan*/  __sort_thin_deferred_bios (struct thin_c*) ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 scalar_t__ bio_list_empty (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 scalar_t__ ensure_next_mapping (struct pool*) ; 
 int /*<<< orphan*/  requeue_bio_list (struct thin_c*,struct bio_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct thin_c*,struct bio*) ; 
 int /*<<< orphan*/  stub2 (struct thin_c*,struct bio*) ; 

__attribute__((used)) static void process_thin_deferred_bios(struct thin_c *tc)
{
	struct pool *pool = tc->pool;
	unsigned long flags;
	struct bio *bio;
	struct bio_list bios;

	if (tc->requeue_mode) {
		requeue_bio_list(tc, &tc->deferred_bio_list);
		return;
	}

	bio_list_init(&bios);

	spin_lock_irqsave(&tc->lock, flags);

	if (bio_list_empty(&tc->deferred_bio_list)) {
		spin_unlock_irqrestore(&tc->lock, flags);
		return;
	}

	__sort_thin_deferred_bios(tc);

	bio_list_merge(&bios, &tc->deferred_bio_list);
	bio_list_init(&tc->deferred_bio_list);

	spin_unlock_irqrestore(&tc->lock, flags);

	while ((bio = bio_list_pop(&bios))) {
		/*
		 * If we've got no free new_mapping structs, and processing
		 * this bio might require one, we pause until there are some
		 * prepared mappings to process.
		 */
		if (ensure_next_mapping(pool)) {
			spin_lock_irqsave(&tc->lock, flags);
			bio_list_add(&tc->deferred_bio_list, bio);
			bio_list_merge(&tc->deferred_bio_list, &bios);
			spin_unlock_irqrestore(&tc->lock, flags);
			break;
		}

		if (bio->bi_rw & BIO_DISCARD)
			pool->process_discard(tc, bio);
		else
			pool->process_bio(tc, bio);
	}
}