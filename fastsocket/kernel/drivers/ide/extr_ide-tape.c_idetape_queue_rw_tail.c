#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request {int* cmd; scalar_t__ errors; scalar_t__ resid_len; int /*<<< orphan*/  __sector; int /*<<< orphan*/  rq_disk; int /*<<< orphan*/  cmd_type; } ;
struct TYPE_4__ {int blk_size; int valid; int /*<<< orphan*/  buf; int /*<<< orphan*/  cur; int /*<<< orphan*/  disk; int /*<<< orphan*/  first_frame; } ;
typedef  TYPE_1__ idetape_tape_t ;
struct TYPE_5__ {int /*<<< orphan*/  queue; TYPE_1__* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 scalar_t__ IDE_DRV_ERROR_GENERAL ; 
 int /*<<< orphan*/  READ ; 
 int REQ_IDETAPE_READ ; 
 int REQ_IDETAPE_WRITE ; 
 int /*<<< orphan*/  REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_kern (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int idetape_queue_rw_tail(ide_drive_t *drive, int cmd, int size)
{
	idetape_tape_t *tape = drive->driver_data;
	struct request *rq;
	int ret;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%x, size: %d", cmd, size);

	BUG_ON(cmd != REQ_IDETAPE_READ && cmd != REQ_IDETAPE_WRITE);
	BUG_ON(size < 0 || size % tape->blk_size);

	rq = blk_get_request(drive->queue, READ, __GFP_WAIT);
	rq->cmd_type = REQ_TYPE_SPECIAL;
	rq->cmd[13] = cmd;
	rq->rq_disk = tape->disk;
	rq->__sector = tape->first_frame;

	if (size) {
		ret = blk_rq_map_kern(drive->queue, rq, tape->buf, size,
				      __GFP_WAIT);
		if (ret)
			goto out_put;
	}

	blk_execute_rq(drive->queue, tape->disk, rq, 0);

	/* calculate the number of transferred bytes and update buffer state */
	size -= rq->resid_len;
	tape->cur = tape->buf;
	if (cmd == REQ_IDETAPE_READ)
		tape->valid = size;
	else
		tape->valid = 0;

	ret = size;
	if (rq->errors == IDE_DRV_ERROR_GENERAL)
		ret = -EIO;
out_put:
	blk_put_request(rq);
	return ret;
}