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
struct request_queue {int dummy; } ;
struct block_device {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bio*) ; 
 struct bio* __bio_map_user_iov (struct request_queue*,struct block_device*,struct sg_iovec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 

struct bio *bio_map_user_iov(struct request_queue *q, struct block_device *bdev,
			     struct sg_iovec *iov, int iov_count,
			     int write_to_vm, gfp_t gfp_mask)
{
	struct bio *bio;

	bio = __bio_map_user_iov(q, bdev, iov, iov_count, write_to_vm,
				 gfp_mask);
	if (IS_ERR(bio))
		return bio;

	/*
	 * subtle -- if __bio_map_user() ended up bouncing a bio,
	 * it would normally disappear when its bi_end_io is run.
	 * however, we need it for the unmap, so grab an extra
	 * reference to it
	 */
	bio_get(bio);

	return bio;
}