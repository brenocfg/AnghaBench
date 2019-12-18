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
struct request_queue {int /*<<< orphan*/  (* unplug_fn ) (struct request_queue*) ;} ;
struct bio_list {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_bdev; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*) ; 
 int /*<<< orphan*/  submit_bio (int,struct bio*) ; 

__attribute__((used)) static void iblock_submit_bios(struct bio_list *list, int rw)
{
	struct bio *bio;
	struct request_queue *q = NULL;

	while ((bio = bio_list_pop(list))) {
		submit_bio(rw, bio);
		q = bdev_get_queue(bio->bi_bdev);
	}

	if (q && q->unplug_fn)
		q->unplug_fn(q);
}