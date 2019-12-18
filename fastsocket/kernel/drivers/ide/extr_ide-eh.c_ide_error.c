#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct request {scalar_t__ cmd_type; int errors; struct ide_cmd* special; } ;
struct ide_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_10__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_9__ {struct request* rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ REQ_TYPE_ATA_TASKFILE ; 
 scalar_t__ REQ_TYPE_FS ; 
 int /*<<< orphan*/  __ide_error (TYPE_2__*,struct request*,int,int) ; 
 scalar_t__ blk_pm_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ide_complete_cmd (TYPE_2__*,struct ide_cmd*,int,int) ; 
 int /*<<< orphan*/  ide_complete_pm_rq (TYPE_2__*,struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ide_dump_status (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  ide_stopped ; 

ide_startstop_t ide_error(ide_drive_t *drive, const char *msg, u8 stat)
{
	struct request *rq;
	u8 err;

	err = ide_dump_status(drive, msg, stat);

	rq = drive->hwif->rq;
	if (rq == NULL)
		return ide_stopped;

	/* retry only "normal" I/O: */
	if (rq->cmd_type != REQ_TYPE_FS) {
		if (rq->cmd_type == REQ_TYPE_ATA_TASKFILE) {
			struct ide_cmd *cmd = rq->special;

			if (cmd)
				ide_complete_cmd(drive, cmd, stat, err);
		} else if (blk_pm_request(rq)) {
			rq->errors = 1;
			ide_complete_pm_rq(drive, rq);
			return ide_stopped;
		}
		rq->errors = err;
		ide_complete_rq(drive, err ? -EIO : 0, blk_rq_bytes(rq));
		return ide_stopped;
	}

	return __ide_error(drive, rq, stat, err);
}