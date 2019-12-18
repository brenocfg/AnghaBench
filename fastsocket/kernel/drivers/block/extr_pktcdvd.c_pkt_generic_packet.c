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
struct request_queue {int dummy; } ;
struct request {int timeout; scalar_t__ errors; int /*<<< orphan*/  q; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  cmd; int /*<<< orphan*/  cmd_len; } ;
struct pktcdvd_device {TYPE_1__* bdev; } ;
struct packet_command {scalar_t__ data_direction; scalar_t__ quiet; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDROM_PACKET_SIZE ; 
 scalar_t__ CGC_DATA_WRITE ; 
 int /*<<< orphan*/  COMMAND_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENODEV ; 
 int HZ ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_QUIET ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 struct request_queue* bdev_get_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 scalar_t__ blk_rq_map_kern (struct request_queue*,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkt_generic_packet(struct pktcdvd_device *pd, struct packet_command *cgc)
{
	struct request_queue *q = bdev_get_queue(pd->bdev);
	struct request *rq;
	int ret = 0;

	rq = blk_get_request(q, (cgc->data_direction == CGC_DATA_WRITE) ?
			     WRITE : READ, __GFP_WAIT);
	if (!rq)
		return -ENODEV;

	if (cgc->buflen) {
		if (blk_rq_map_kern(q, rq, cgc->buffer, cgc->buflen, __GFP_WAIT))
			goto out;
	}

	rq->cmd_len = COMMAND_SIZE(cgc->cmd[0]);
	memcpy(rq->cmd, cgc->cmd, CDROM_PACKET_SIZE);

	rq->timeout = 60*HZ;
	rq->cmd_type = REQ_TYPE_BLOCK_PC;
	if (cgc->quiet)
		rq->cmd_flags |= REQ_QUIET;

	blk_execute_rq(rq->q, pd->bdev->bd_disk, rq, 0);
	if (rq->errors)
		ret = -EIO;
out:
	blk_put_request(rq);
	return ret;
}