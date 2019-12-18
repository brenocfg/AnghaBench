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
struct sg_io_hdr {int /*<<< orphan*/  timeout; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmdp; } ;
struct request_queue {scalar_t__ sg_timeout; } ;
struct request {scalar_t__ timeout; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmd; } ;
typedef  int fmode_t ;

/* Variables and functions */
 scalar_t__ BLK_DEFAULT_SG_TIMEOUT ; 
 scalar_t__ BLK_MIN_SG_TIMEOUT ; 
 int EFAULT ; 
 int EPERM ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 scalar_t__ blk_verify_command (struct request_queue*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blk_fill_sghdr_rq(struct request_queue *q, struct request *rq,
			     struct sg_io_hdr *hdr, fmode_t mode)
{
	if (copy_from_user(rq->cmd, hdr->cmdp, hdr->cmd_len))
		return -EFAULT;
	if (blk_verify_command(q, rq->cmd, mode & FMODE_WRITE))
		return -EPERM;

	/*
	 * fill in request structure
	 */
	rq->cmd_len = hdr->cmd_len;
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