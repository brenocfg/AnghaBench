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
struct scsi_device {struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;
struct request {int cmd_flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  retries; int /*<<< orphan*/  cmd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  RDAC_RETRIES ; 
 int /*<<< orphan*/  RDAC_TIMEOUT ; 
 int REQ_FAILFAST_DEV ; 
 int REQ_FAILFAST_DRIVER ; 
 int REQ_FAILFAST_TRANSPORT ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 struct request* blk_get_request (struct request_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 scalar_t__ blk_rq_map_kern (struct request_queue*,struct request*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 

__attribute__((used)) static struct request *get_rdac_req(struct scsi_device *sdev,
			void *buffer, unsigned buflen, int rw)
{
	struct request *rq;
	struct request_queue *q = sdev->request_queue;

	rq = blk_get_request(q, rw, GFP_NOIO);

	if (!rq) {
		sdev_printk(KERN_INFO, sdev,
				"get_rdac_req: blk_get_request failed.\n");
		return NULL;
	}

	if (buflen && blk_rq_map_kern(q, rq, buffer, buflen, GFP_NOIO)) {
		blk_put_request(rq);
		sdev_printk(KERN_INFO, sdev,
				"get_rdac_req: blk_rq_map_kern failed.\n");
		return NULL;
	}

	rq->cmd_type = REQ_TYPE_BLOCK_PC;
	rq->cmd_flags |= REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
			 REQ_FAILFAST_DRIVER;
	rq->retries = RDAC_RETRIES;
	rq->timeout = RDAC_TIMEOUT;

	return rq;
}