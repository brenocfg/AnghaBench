#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {char* special; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  cmd_type; } ;
struct ide_atapi_pc {int /*<<< orphan*/  c; } ;
struct gendisk {int dummy; } ;
struct TYPE_3__ {scalar_t__ media; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_IDETAPE_PC1 ; 
 int /*<<< orphan*/  REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int blk_execute_rq (int /*<<< orphan*/ ,struct gendisk*,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_kern (int /*<<< orphan*/ ,struct request*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_tape ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int ide_queue_pc_tail(ide_drive_t *drive, struct gendisk *disk,
		      struct ide_atapi_pc *pc, void *buf, unsigned int bufflen)
{
	struct request *rq;
	int error;

	rq = blk_get_request(drive->queue, READ, __GFP_WAIT);
	rq->cmd_type = REQ_TYPE_SPECIAL;
	rq->special = (char *)pc;

	if (buf && bufflen) {
		error = blk_rq_map_kern(drive->queue, rq, buf, bufflen,
					GFP_NOIO);
		if (error)
			goto put_req;
	}

	memcpy(rq->cmd, pc->c, 12);
	if (drive->media == ide_tape)
		rq->cmd[13] = REQ_IDETAPE_PC1;
	error = blk_execute_rq(drive->queue, disk, rq, 0);
put_req:
	blk_put_request(rq);
	return error;
}