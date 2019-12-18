#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct request {int cmd_type; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * cmd; } ;
struct ide_cmd {struct request* rq; int /*<<< orphan*/  tf_flags; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_9__ {int debug_mask; } ;
typedef  TYPE_1__ ide_drive_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_WAIT_PC ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EIO ; 
 int IDE_DBG_RQ ; 
 int /*<<< orphan*/  IDE_TFLAG_WRITE ; 
#define  REQ_TYPE_ATA_PC 132 
#define  REQ_TYPE_BLOCK_PC 131 
#define  REQ_TYPE_FS 130 
#define  REQ_TYPE_SENSE 129 
#define  REQ_TYPE_SPECIAL 128 
 int /*<<< orphan*/  blk_dump_rq_flags (struct request*,char*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  cdrom_do_block_pc (TYPE_1__*,struct request*) ; 
 int /*<<< orphan*/  cdrom_start_rw (TYPE_1__*,struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ide_debug_log (int,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ide_init_sg_cmd (struct ide_cmd*,scalar_t__) ; 
 int /*<<< orphan*/  ide_issue_pc (TYPE_1__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_map_sg (TYPE_1__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_prep_sense (TYPE_1__*,struct request*) ; 
 int /*<<< orphan*/  ide_stopped ; 
 int /*<<< orphan*/  memset (struct ide_cmd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static ide_startstop_t ide_cd_do_request(ide_drive_t *drive, struct request *rq,
					sector_t block)
{
	struct ide_cmd cmd;
	int uptodate = 0, nsectors;

	ide_debug_log(IDE_DBG_RQ, "cmd: 0x%x, block: %llu",
				  rq->cmd[0], (unsigned long long)block);

	if (drive->debug_mask & IDE_DBG_RQ)
		blk_dump_rq_flags(rq, "ide_cd_do_request");

	switch (rq->cmd_type) {
	case REQ_TYPE_FS:
		if (cdrom_start_rw(drive, rq) == ide_stopped)
			goto out_end;
		break;
	case REQ_TYPE_SENSE:
	case REQ_TYPE_BLOCK_PC:
	case REQ_TYPE_ATA_PC:
		if (!rq->timeout)
			rq->timeout = ATAPI_WAIT_PC;

		cdrom_do_block_pc(drive, rq);
		break;
	case REQ_TYPE_SPECIAL:
		/* right now this can only be a reset... */
		uptodate = 1;
		goto out_end;
	default:
		BUG();
	}

	/* prepare sense request for this command */
	ide_prep_sense(drive, rq);

	memset(&cmd, 0, sizeof(cmd));

	if (rq_data_dir(rq))
		cmd.tf_flags |= IDE_TFLAG_WRITE;

	cmd.rq = rq;

	if (rq->cmd_type == REQ_TYPE_FS || blk_rq_bytes(rq)) {
		ide_init_sg_cmd(&cmd, blk_rq_bytes(rq));
		ide_map_sg(drive, &cmd);
	}

	return ide_issue_pc(drive, &cmd);
out_end:
	nsectors = blk_rq_sectors(rq);

	if (nsectors == 0)
		nsectors = 1;

	ide_complete_rq(drive, uptodate ? 0 : -EIO, nsectors << 9);

	return ide_stopped;
}