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
struct sg_iovec {int /*<<< orphan*/  iov_len; scalar_t__ iov_base; } ;
struct rq_map_data {int dummy; } ;
struct request_queue {unsigned int dma_pad_mask; } ;
struct request {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  cmd_flags; } ;
struct bio {unsigned int bi_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_USER_MAPPED ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct bio*) ; 
 int PTR_ERR (struct bio*) ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  REQ_COPY_USER ; 
 int /*<<< orphan*/  __blk_rq_unmap_user (struct bio*) ; 
 struct bio* bio_copy_user_iov (struct request_queue*,struct rq_map_data*,struct sg_iovec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 struct bio* bio_map_user_iov (struct request_queue*,int /*<<< orphan*/ *,struct sg_iovec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_bounce (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  blk_rq_bio_prep (struct request_queue*,struct request*,struct bio*) ; 
 unsigned long queue_dma_alignment (struct request_queue*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

int blk_rq_map_user_iov(struct request_queue *q, struct request *rq,
			struct rq_map_data *map_data, struct sg_iovec *iov,
			int iov_count, unsigned int len, gfp_t gfp_mask)
{
	struct bio *bio;
	int i, read = rq_data_dir(rq) == READ;
	int unaligned = 0;

	if (!iov || iov_count <= 0)
		return -EINVAL;

	for (i = 0; i < iov_count; i++) {
		unsigned long uaddr = (unsigned long)iov[i].iov_base;

		if (!iov[i].iov_len)
			return -EINVAL;

		if (uaddr & queue_dma_alignment(q)) {
			unaligned = 1;
			break;
		}
	}

	if (unaligned || (q->dma_pad_mask & len) || map_data)
		bio = bio_copy_user_iov(q, map_data, iov, iov_count, read,
					gfp_mask);
	else
		bio = bio_map_user_iov(q, NULL, iov, iov_count, read, gfp_mask);

	if (IS_ERR(bio))
		return PTR_ERR(bio);

	if (bio->bi_size != len) {
		/*
		 * Grab an extra reference to this bio, as bio_unmap_user()
		 * expects to be able to drop it twice as it happens on the
		 * normal IO completion path
		 */
		bio_get(bio);
		bio_endio(bio, 0);
		__blk_rq_unmap_user(bio);
		return -EINVAL;
	}

	if (!bio_flagged(bio, BIO_USER_MAPPED))
		rq->cmd_flags |= REQ_COPY_USER;

	blk_queue_bounce(q, &bio);
	bio_get(bio);
	blk_rq_bio_prep(q, rq, bio);
	rq->buffer = NULL;
	return 0;
}