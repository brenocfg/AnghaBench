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
struct request_queue {struct dst_node* queuedata; } ;
struct dst_node {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ bio_empty_barrier (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 
 int dst_process_bio (struct dst_node*,struct bio*) ; 

__attribute__((used)) static int dst_request(struct request_queue *q, struct bio *bio)
{
	struct dst_node *n = q->queuedata;
	int err = -EIO;

	if (bio_empty_barrier(bio) && !blk_queue_discard(q)) {
		/*
		 * This is a dirty^Wnice hack, but if we complete this
		 * operation with -EOPNOTSUPP like intended, XFS
		 * will stuck and freeze the machine. This may be
		 * not particulary XFS problem though, but it is the
		 * only FS which sends empty barrier at umount time
		 * I worked with.
		 *
		 * Empty barriers are not allowed anyway, see 51fd77bd9f512
		 * for example, although later it was changed to
		 * bio_rw_flagged(bio, BIO_RW_DISCARD) only, which does not
		 * work in this case.
		 */
		//err = -EOPNOTSUPP;
		err = 0;
		goto end_io;
	}

	bio_get(bio);

	return dst_process_bio(n, bio);

end_io:
	bio_endio(bio, err);
	return err;
}