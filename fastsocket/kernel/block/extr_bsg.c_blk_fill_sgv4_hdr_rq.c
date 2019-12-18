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
struct sg_io_v4 {scalar_t__ request_len; scalar_t__ subprotocol; int /*<<< orphan*/  timeout; scalar_t__ request; } ;
struct request_queue {scalar_t__ sg_timeout; } ;
struct request {scalar_t__ cmd_len; scalar_t__ timeout; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  cmd; } ;
struct bsg_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 scalar_t__ BLK_DEFAULT_SG_TIMEOUT ; 
 scalar_t__ BLK_MAX_CDB ; 
 scalar_t__ BLK_MIN_SG_TIMEOUT ; 
 scalar_t__ BSG_SUB_PROTOCOL_SCSI_CMD ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EFAULT ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 scalar_t__ blk_verify_command (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blk_fill_sgv4_hdr_rq(struct request_queue *q, struct request *rq,
				struct sg_io_v4 *hdr, struct bsg_device *bd,
				fmode_t has_write_perm)
{
	if (hdr->request_len > BLK_MAX_CDB) {
		rq->cmd = kzalloc(hdr->request_len, GFP_KERNEL);
		if (!rq->cmd)
			return -ENOMEM;
	}

	if (copy_from_user(rq->cmd, (void *)(unsigned long)hdr->request,
			   hdr->request_len))
		return -EFAULT;

	if (hdr->subprotocol == BSG_SUB_PROTOCOL_SCSI_CMD) {
		if (blk_verify_command(q, rq->cmd, has_write_perm))
			return -EPERM;
	} else if (!capable(CAP_SYS_RAWIO))
		return -EPERM;

	/*
	 * fill in request structure
	 */
	rq->cmd_len = hdr->request_len;
	rq->cmd_type = REQ_TYPE_BLOCK_PC;

	rq->timeout = msecs_to_jiffies(hdr->timeout);
	if (!rq->timeout)
		rq->timeout = q->sg_timeout;
	if (!rq->timeout)
		rq->timeout = BLK_DEFAULT_SG_TIMEOUT;
	if (rq->timeout < BLK_MIN_SG_TIMEOUT)
		rq->timeout = BLK_MIN_SG_TIMEOUT;

	return 0;
}