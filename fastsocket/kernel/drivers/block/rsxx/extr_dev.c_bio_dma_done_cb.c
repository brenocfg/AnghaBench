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
struct rsxx_cardinfo {scalar_t__ gendisk; int /*<<< orphan*/  eeh_state; } ;
struct rsxx_bio_meta {int /*<<< orphan*/  error; int /*<<< orphan*/  bio; int /*<<< orphan*/  start_time; int /*<<< orphan*/  pending_dmas; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_endio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_meta_pool ; 
 int /*<<< orphan*/  disk_stats_complete (struct rsxx_cardinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rsxx_bio_meta*) ; 

__attribute__((used)) static void bio_dma_done_cb(struct rsxx_cardinfo *card,
			    void *cb_data,
			    unsigned int error)
{
	struct rsxx_bio_meta *meta = cb_data;

	if (error)
		atomic_set(&meta->error, 1);

	if (atomic_dec_and_test(&meta->pending_dmas)) {
		if (!card->eeh_state && card->gendisk)
			disk_stats_complete(card, meta->bio, meta->start_time);

		bio_endio(meta->bio, atomic_read(&meta->error) ? -EIO : 0);
		kmem_cache_free(bio_meta_pool, meta);
	}
}