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
struct throtl_grp {int /*<<< orphan*/ * nr_queued; int /*<<< orphan*/ * bio_lists; } ;
struct throtl_data {int /*<<< orphan*/ * nr_queued; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  throtl_enqueue_tg (struct throtl_data*,struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_ref_get_tg (struct throtl_grp*) ; 

__attribute__((used)) static void throtl_add_bio_tg(struct throtl_data *td, struct throtl_grp *tg,
			struct bio *bio)
{
	bool rw = bio_data_dir(bio);

	bio_list_add(&tg->bio_lists[rw], bio);
	/* Take a bio reference on tg */
	throtl_ref_get_tg(tg);
	tg->nr_queued[rw]++;
	td->nr_queued[rw]++;
	throtl_enqueue_tg(td, tg);
}