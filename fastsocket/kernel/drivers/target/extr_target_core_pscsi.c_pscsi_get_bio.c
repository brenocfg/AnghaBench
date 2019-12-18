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
struct bio {int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bio* bio_kmalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pscsi_bi_endio ; 

__attribute__((used)) static inline struct bio *pscsi_get_bio(int nr_vecs)
{
	struct bio *bio;
	/*
	 * Use bio_malloc() following the comment in for bio -> struct request
	 * in block/blk-core.c:blk_make_request()
	 */
	bio = bio_kmalloc(GFP_KERNEL, nr_vecs);
	if (!bio) {
		pr_err("PSCSI: bio_kmalloc() failed\n");
		return NULL;
	}
	bio->bi_end_io = pscsi_bi_endio;

	return bio;
}