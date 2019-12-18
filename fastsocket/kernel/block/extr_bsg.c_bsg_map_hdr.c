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
typedef  int /*<<< orphan*/  u8 ;
struct sg_io_v4 {int dout_xfer_len; unsigned int din_xfer_len; scalar_t__ din_xferp; scalar_t__ dout_xferp; } ;
struct bsg_class_device {int /*<<< orphan*/  class_dev; } ;
struct request_queue {int /*<<< orphan*/  queue_flags; struct bsg_class_device bsg_dev; } ;
struct request {scalar_t__ cmd; scalar_t__ __cmd; int /*<<< orphan*/  bio; scalar_t__ sense_len; int /*<<< orphan*/ * sense; int /*<<< orphan*/  cmd_type; struct request* next_rq; } ;
struct bsg_device {struct request_queue* queue; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 struct request* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_FLAG_BIDI ; 
 int READ ; 
 int WRITE ; 
 int blk_fill_sgv4_hdr_rq (struct request_queue*,struct request*,struct sg_io_v4*,struct bsg_device*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (struct request_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_user (struct request_queue*,struct request*,int /*<<< orphan*/ *,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_unmap_user (int /*<<< orphan*/ ) ; 
 int bsg_validate_sgv4_hdr (struct request_queue*,struct sg_io_v4*,int*) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned long long,int,unsigned long long,unsigned int) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct request *
bsg_map_hdr(struct bsg_device *bd, struct sg_io_v4 *hdr, fmode_t has_write_perm,
	    u8 *sense)
{
	struct request_queue *q = bd->queue;
	struct request *rq, *next_rq = NULL;
	int ret, rw;
	unsigned int dxfer_len;
	void *dxferp = NULL;
	struct bsg_class_device *bcd = &q->bsg_dev;

	/* if the LLD has been removed then the bsg_unregister_queue will
	 * eventually be called and the class_dev was freed, so we can no
	 * longer use this request_queue. Return no such address.
	 */
	if (!bcd->class_dev)
		return ERR_PTR(-ENXIO);

	dprintk("map hdr %llx/%u %llx/%u\n", (unsigned long long) hdr->dout_xferp,
		hdr->dout_xfer_len, (unsigned long long) hdr->din_xferp,
		hdr->din_xfer_len);

	ret = bsg_validate_sgv4_hdr(q, hdr, &rw);
	if (ret)
		return ERR_PTR(ret);

	/*
	 * map scatter-gather elements seperately and string them to request
	 */
	rq = blk_get_request(q, rw, GFP_KERNEL);
	if (!rq)
		return ERR_PTR(-ENODEV);
	ret = blk_fill_sgv4_hdr_rq(q, rq, hdr, bd, has_write_perm);
	if (ret)
		goto out;

	if (rw == WRITE && hdr->din_xfer_len) {
		if (!test_bit(QUEUE_FLAG_BIDI, &q->queue_flags)) {
			ret = -EOPNOTSUPP;
			goto out;
		}

		next_rq = blk_get_request(q, READ, GFP_KERNEL);
		if (!next_rq) {
			ret = -ENODEV;
			goto out;
		}
		rq->next_rq = next_rq;
		next_rq->cmd_type = rq->cmd_type;

		dxferp = (void*)(unsigned long)hdr->din_xferp;
		ret =  blk_rq_map_user(q, next_rq, NULL, dxferp,
				       hdr->din_xfer_len, GFP_KERNEL);
		if (ret)
			goto out;
	}

	if (hdr->dout_xfer_len) {
		dxfer_len = hdr->dout_xfer_len;
		dxferp = (void*)(unsigned long)hdr->dout_xferp;
	} else if (hdr->din_xfer_len) {
		dxfer_len = hdr->din_xfer_len;
		dxferp = (void*)(unsigned long)hdr->din_xferp;
	} else
		dxfer_len = 0;

	if (dxfer_len) {
		ret = blk_rq_map_user(q, rq, NULL, dxferp, dxfer_len,
				      GFP_KERNEL);
		if (ret)
			goto out;
	}

	rq->sense = sense;
	rq->sense_len = 0;

	return rq;
out:
	if (rq->cmd != rq->__cmd)
		kfree(rq->cmd);
	blk_put_request(rq);
	if (next_rq) {
		blk_rq_unmap_user(next_rq->bio);
		blk_put_request(next_rq);
	}
	return ERR_PTR(ret);
}