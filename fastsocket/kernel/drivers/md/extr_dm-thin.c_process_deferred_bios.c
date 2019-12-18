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
struct thin_c {int dummy; } ;
struct bio_list {int dummy; } ;
struct pool {int /*<<< orphan*/  last_commit_jiffies; int /*<<< orphan*/  pmd; int /*<<< orphan*/  lock; struct bio_list deferred_flush_bios; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_list_empty (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 scalar_t__ commit (struct pool*) ; 
 scalar_t__ dm_pool_changed_this_transaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 struct thin_c* get_first_thin (struct pool*) ; 
 struct thin_c* get_next_thin (struct pool*,struct thin_c*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ need_commit_due_to_time (struct pool*) ; 
 int /*<<< orphan*/  process_thin_deferred_bios (struct thin_c*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void process_deferred_bios(struct pool *pool)
{
	unsigned long flags;
	struct bio *bio;
	struct bio_list bios;
	struct thin_c *tc;

	tc = get_first_thin(pool);
	while (tc) {
		process_thin_deferred_bios(tc);
		tc = get_next_thin(pool, tc);
	}

	/*
	 * If there are any deferred flush bios, we must commit
	 * the metadata before issuing them.
	 */
	bio_list_init(&bios);
	spin_lock_irqsave(&pool->lock, flags);
	bio_list_merge(&bios, &pool->deferred_flush_bios);
	bio_list_init(&pool->deferred_flush_bios);
	spin_unlock_irqrestore(&pool->lock, flags);

	if (bio_list_empty(&bios) &&
	    !(dm_pool_changed_this_transaction(pool->pmd) && need_commit_due_to_time(pool)))
		return;

	if (commit(pool)) {
		while ((bio = bio_list_pop(&bios)))
			bio_io_error(bio);
		return;
	}
	pool->last_commit_jiffies = jiffies;

	while ((bio = bio_list_pop(&bios)))
		generic_make_request(bio);
}