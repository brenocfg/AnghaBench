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
struct sg_iovec {int dummy; } ;
struct bio_vec {int dummy; } ;
struct bio_map_data {int nr_sgvecs; int is_our_pages; int /*<<< orphan*/  sgvecs; int /*<<< orphan*/  iovecs; } ;
struct bio {int bi_vcnt; struct bio_map_data* bi_private; struct sg_iovec* bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct sg_iovec*,int) ; 

__attribute__((used)) static void bio_set_map_data(struct bio_map_data *bmd, struct bio *bio,
			     struct sg_iovec *iov, int iov_count,
			     int is_our_pages)
{
	memcpy(bmd->iovecs, bio->bi_io_vec, sizeof(struct bio_vec) * bio->bi_vcnt);
	memcpy(bmd->sgvecs, iov, sizeof(struct sg_iovec) * iov_count);
	bmd->nr_sgvecs = iov_count;
	bmd->is_our_pages = is_our_pages;
	bio->bi_private = bmd;
}