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
struct throtl_data {scalar_t__* nr_queued; } ;
struct bio_list {int dummy; } ;
struct bio {int bi_rw; } ;

/* Variables and functions */
 int BIO_RW_THROTTLED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throtl_charge_bio (struct throtl_grp*,struct bio*) ; 
 int /*<<< orphan*/  throtl_put_tg (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_trim_slice (struct throtl_data*,struct throtl_grp*,int) ; 

__attribute__((used)) static void tg_dispatch_one_bio(struct throtl_data *td, struct throtl_grp *tg,
				bool rw, struct bio_list *bl)
{
	struct bio *bio;

	bio = bio_list_pop(&tg->bio_lists[rw]);
	tg->nr_queued[rw]--;
	/* Drop bio reference on tg */
	throtl_put_tg(tg);

	BUG_ON(td->nr_queued[rw] <= 0);
	td->nr_queued[rw]--;

	throtl_charge_bio(tg, bio);
	bio_list_add(bl, bio);
	bio->bi_rw |= (1 << BIO_RW_THROTTLED);

	throtl_trim_slice(td, tg, rw);
}