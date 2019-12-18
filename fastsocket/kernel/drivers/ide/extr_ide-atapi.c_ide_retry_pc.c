#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  q; int /*<<< orphan*/  cmd; } ;
struct ide_atapi_pc {int /*<<< orphan*/  c; } ;
struct TYPE_8__ {scalar_t__ media; TYPE_1__* hwif; int /*<<< orphan*/  atapi_flags; struct ide_atapi_pc request_sense_pc; struct request sense_rq; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_7__ {struct request* rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IDE_AFLAG_IGNORE_DSC ; 
 int /*<<< orphan*/  blk_requeue_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 scalar_t__ ide_queue_sense_rq (TYPE_2__*,struct ide_atapi_pc*) ; 
 int /*<<< orphan*/  ide_read_error (TYPE_2__*) ; 
 scalar_t__ ide_tape ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ide_retry_pc(ide_drive_t *drive)
{
	struct request *failed_rq = drive->hwif->rq;
	struct request *sense_rq = &drive->sense_rq;
	struct ide_atapi_pc *pc = &drive->request_sense_pc;

	(void)ide_read_error(drive);

	/* init pc from sense_rq */
	ide_init_pc(pc);
	memcpy(pc->c, sense_rq->cmd, 12);

	if (drive->media == ide_tape)
		drive->atapi_flags |= IDE_AFLAG_IGNORE_DSC;

	/*
	 * Push back the failed request and put request sense on top
	 * of it.  The failed command will be retried after sense data
	 * is acquired.
	 */
	blk_requeue_request(failed_rq->q, failed_rq);
	drive->hwif->rq = NULL;
	if (ide_queue_sense_rq(drive, pc)) {
		blk_start_request(failed_rq);
		ide_complete_rq(drive, -EIO, blk_rq_bytes(failed_rq));
	}
}