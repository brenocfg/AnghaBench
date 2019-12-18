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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;
struct request {int* cmd; int cmd_flags; int /*<<< orphan*/  q; int /*<<< orphan*/  retries; int /*<<< orphan*/  timeout; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  cmd_len; } ;
typedef  int /*<<< orphan*/  short_trespass ;
typedef  int /*<<< orphan*/  long_trespass ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CLARIION_BUFFER_SIZE ; 
 int /*<<< orphan*/  CLARIION_RETRIES ; 
 int /*<<< orphan*/  CLARIION_TIMEOUT ; 
 int /*<<< orphan*/  COMMAND_SIZE (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
#define  INQUIRY 130 
 int /*<<< orphan*/  KERN_INFO ; 
#define  MODE_SELECT 129 
#define  MODE_SELECT_10 128 
 int /*<<< orphan*/  READ ; 
 int REQ_FAILFAST_DEV ; 
 int REQ_FAILFAST_DRIVER ; 
 int REQ_FAILFAST_TRANSPORT ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 int /*<<< orphan*/  WRITE ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 scalar_t__ blk_rq_map_kern (int /*<<< orphan*/ ,struct request*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 

__attribute__((used)) static struct request *get_req(struct scsi_device *sdev, int cmd,
				unsigned char *buffer)
{
	struct request *rq;
	int len = 0;

	rq = blk_get_request(sdev->request_queue,
			(cmd != INQUIRY) ? WRITE : READ, GFP_NOIO);
	if (!rq) {
		sdev_printk(KERN_INFO, sdev, "get_req: blk_get_request failed");
		return NULL;
	}

	rq->cmd_len = COMMAND_SIZE(cmd);
	rq->cmd[0] = cmd;

	switch (cmd) {
	case MODE_SELECT:
		len = sizeof(short_trespass);
		rq->cmd[1] = 0x10;
		rq->cmd[4] = len;
		break;
	case MODE_SELECT_10:
		len = sizeof(long_trespass);
		rq->cmd[1] = 0x10;
		rq->cmd[8] = len;
		break;
	case INQUIRY:
		len = CLARIION_BUFFER_SIZE;
		rq->cmd[4] = len;
		memset(buffer, 0, len);
		break;
	default:
		BUG_ON(1);
		break;
	}

	rq->cmd_type = REQ_TYPE_BLOCK_PC;
	rq->cmd_flags |= REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
			 REQ_FAILFAST_DRIVER;
	rq->timeout = CLARIION_TIMEOUT;
	rq->retries = CLARIION_RETRIES;

	if (blk_rq_map_kern(rq->q, rq, buffer, len, GFP_NOIO)) {
		blk_put_request(rq);
		return NULL;
	}

	return rq;
}