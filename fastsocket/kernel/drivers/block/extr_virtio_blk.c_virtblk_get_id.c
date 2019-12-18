#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtio_blk {TYPE_1__* disk; } ;
struct request {int /*<<< orphan*/  cmd_type; } ;
struct gendisk {struct virtio_blk* private_data; } ;
struct bio {int /*<<< orphan*/  cmd_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  VIRTIO_BLK_ID_BYTES ; 
 struct request* bio_map_kern (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct request*) ; 
 int blk_execute_rq (int /*<<< orphan*/ ,TYPE_1__*,struct request*,int) ; 
 struct request* blk_make_request (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 

__attribute__((used)) static int virtblk_get_id(struct gendisk *disk, char *id_str)
{
	struct virtio_blk *vblk = disk->private_data;
	struct request *req;
	struct bio *bio;
	int err;

	bio = bio_map_kern(vblk->disk->queue, id_str, VIRTIO_BLK_ID_BYTES,
			   GFP_KERNEL);
	if (IS_ERR(bio))
		return PTR_ERR(bio);

	req = blk_make_request(vblk->disk->queue, bio, GFP_KERNEL);
	if (IS_ERR(req)) {
		bio_put(bio);
		return PTR_ERR(req);
	}

	req->cmd_type = REQ_TYPE_SPECIAL;
	err = blk_execute_rq(vblk->disk->queue, vblk->disk, req, false);
	blk_put_request(req);

	return err;
}