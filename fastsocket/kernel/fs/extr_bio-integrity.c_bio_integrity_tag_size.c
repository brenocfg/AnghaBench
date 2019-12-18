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
struct blk_integrity {unsigned int tag_size; unsigned int sector_size; } ;
struct bio {unsigned int bi_size; int /*<<< orphan*/  bi_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct blk_integrity* bdev_get_integrity (int /*<<< orphan*/ ) ; 

unsigned int bio_integrity_tag_size(struct bio *bio)
{
	struct blk_integrity *bi = bdev_get_integrity(bio->bi_bdev);

	BUG_ON(bio->bi_size == 0);

	return bi->tag_size * (bio->bi_size / bi->sector_size);
}