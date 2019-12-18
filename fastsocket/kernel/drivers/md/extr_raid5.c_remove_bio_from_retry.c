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
struct r5conf {struct bio* retry_read_aligned_list; struct bio* retry_read_aligned; } ;
struct bio {struct bio* bi_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  raid5_set_bi_stripes (struct bio*,int) ; 

__attribute__((used)) static struct bio *remove_bio_from_retry(struct r5conf *conf)
{
	struct bio *bi;

	bi = conf->retry_read_aligned;
	if (bi) {
		conf->retry_read_aligned = NULL;
		return bi;
	}
	bi = conf->retry_read_aligned_list;
	if(bi) {
		conf->retry_read_aligned_list = bi->bi_next;
		bi->bi_next = NULL;
		/*
		 * this sets the active strip count to 1 and the processed
		 * strip count to zero (upper 8 bits)
		 */
		raid5_set_bi_stripes(bi, 1); /* biased count of active stripes */
	}

	return bi;
}