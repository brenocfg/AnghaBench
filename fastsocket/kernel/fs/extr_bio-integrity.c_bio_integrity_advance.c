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
struct blk_integrity {unsigned int tuple_size; } ;
struct bio_integrity_payload {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_bdev; struct bio_integrity_payload* bi_integrity; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct blk_integrity* bdev_get_integrity (int /*<<< orphan*/ ) ; 
 unsigned int bio_integrity_hw_sectors (struct blk_integrity*,unsigned int) ; 
 int /*<<< orphan*/  bio_integrity_mark_head (struct bio_integrity_payload*,unsigned int) ; 

void bio_integrity_advance(struct bio *bio, unsigned int bytes_done)
{
	struct bio_integrity_payload *bip = bio->bi_integrity;
	struct blk_integrity *bi = bdev_get_integrity(bio->bi_bdev);
	unsigned int nr_sectors;

	BUG_ON(bip == NULL);
	BUG_ON(bi == NULL);

	nr_sectors = bio_integrity_hw_sectors(bi, bytes_done >> 9);
	bio_integrity_mark_head(bip, nr_sectors * bi->tuple_size);
}