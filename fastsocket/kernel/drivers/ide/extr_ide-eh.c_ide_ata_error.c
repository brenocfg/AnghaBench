#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct request {int errors; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_11__ {int host_flags; TYPE_1__* tp_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_12__ {int dev_flags; int mult_count; int /*<<< orphan*/  special_flags; int /*<<< orphan*/  crc_count; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_10__ {int (* read_status ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int ATA_ABORTED ; 
 int ATA_BBK ; 
 int ATA_BUSY ; 
 int ATA_CMD_INIT_DEV_PARAMS ; 
 int ATA_DF ; 
 int ATA_DRQ ; 
 int ATA_ERR ; 
 int ATA_TRK0NF ; 
 int ATA_UNC ; 
 int BAD_CRC ; 
 int ERROR_MAX ; 
 int ERROR_RECAL ; 
 int ERROR_RESET ; 
 int IDE_DFLAG_LBA ; 
 int IDE_DFLAG_NOWERR ; 
 int IDE_HFLAG_ERROR_STOPS_FIFO ; 
 int /*<<< orphan*/  IDE_SFLAG_RECALIBRATE ; 
 scalar_t__ READ ; 
 int SECTOR_SIZE ; 
 scalar_t__ blk_noretry_request (struct request*) ; 
 int /*<<< orphan*/  ide_do_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  ide_kill_rq (TYPE_3__*,struct request*) ; 
 int /*<<< orphan*/  ide_pad_transfer (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ide_stopped ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*) ; 

__attribute__((used)) static ide_startstop_t ide_ata_error(ide_drive_t *drive, struct request *rq,
				     u8 stat, u8 err)
{
	ide_hwif_t *hwif = drive->hwif;

	if ((stat & ATA_BUSY) ||
	    ((stat & ATA_DF) && (drive->dev_flags & IDE_DFLAG_NOWERR) == 0)) {
		/* other bits are useless when BUSY */
		rq->errors |= ERROR_RESET;
	} else if (stat & ATA_ERR) {
		/* err has different meaning on cdrom and tape */
		if (err == ATA_ABORTED) {
			if ((drive->dev_flags & IDE_DFLAG_LBA) &&
			    /* some newer drives don't support ATA_CMD_INIT_DEV_PARAMS */
			    hwif->tp_ops->read_status(hwif) == ATA_CMD_INIT_DEV_PARAMS)
				return ide_stopped;
		} else if ((err & BAD_CRC) == BAD_CRC) {
			/* UDMA crc error, just retry the operation */
			drive->crc_count++;
		} else if (err & (ATA_BBK | ATA_UNC)) {
			/* retries won't help these */
			rq->errors = ERROR_MAX;
		} else if (err & ATA_TRK0NF) {
			/* help it find track zero */
			rq->errors |= ERROR_RECAL;
		}
	}

	if ((stat & ATA_DRQ) && rq_data_dir(rq) == READ &&
	    (hwif->host_flags & IDE_HFLAG_ERROR_STOPS_FIFO) == 0) {
		int nsect = drive->mult_count ? drive->mult_count : 1;

		ide_pad_transfer(drive, READ, nsect * SECTOR_SIZE);
	}

	if (rq->errors >= ERROR_MAX || blk_noretry_request(rq)) {
		ide_kill_rq(drive, rq);
		return ide_stopped;
	}

	if (hwif->tp_ops->read_status(hwif) & (ATA_BUSY | ATA_DRQ))
		rq->errors |= ERROR_RESET;

	if ((rq->errors & ERROR_RESET) == ERROR_RESET) {
		++rq->errors;
		return ide_do_reset(drive);
	}

	if ((rq->errors & ERROR_RECAL) == ERROR_RECAL)
		drive->special_flags |= IDE_SFLAG_RECALIBRATE;

	++rq->errors;

	return ide_stopped;
}