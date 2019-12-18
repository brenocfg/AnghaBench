#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct request {scalar_t__ cmd_type; int /*<<< orphan*/  errors; scalar_t__ rq_disk; } ;
struct TYPE_4__ {scalar_t__ media; int /*<<< orphan*/ * failed_pc; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IDE_DRV_ERROR_GENERAL ; 
 scalar_t__ REQ_TYPE_FS ; 
 scalar_t__ REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_floppy ; 
 scalar_t__ ide_tape ; 

void ide_kill_rq(ide_drive_t *drive, struct request *rq)
{
	u8 drv_req = (rq->cmd_type == REQ_TYPE_SPECIAL) && rq->rq_disk;
	u8 media = drive->media;

	drive->failed_pc = NULL;

	if ((media == ide_floppy || media == ide_tape) && drv_req) {
		rq->errors = 0;
	} else {
		if (media == ide_tape)
			rq->errors = IDE_DRV_ERROR_GENERAL;
		else if (rq->cmd_type != REQ_TYPE_FS && rq->errors == 0)
			rq->errors = -EIO;
	}

	ide_complete_rq(drive, -EIO, blk_rq_bytes(rq));
}