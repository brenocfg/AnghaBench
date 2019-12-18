#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct request {int errors; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_10__ {TYPE_1__* tp_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_11__ {int dev_flags; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_9__ {int (* read_status ) (TYPE_2__*) ;int /*<<< orphan*/  (* exec_command ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ATA_BUSY ; 
 int /*<<< orphan*/  ATA_CMD_IDLEIMMEDIATE ; 
 int ATA_DF ; 
 int ATA_DRQ ; 
 int ERROR_MAX ; 
 int ERROR_RESET ; 
 int IDE_DFLAG_NOWERR ; 
 int /*<<< orphan*/  ide_do_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  ide_kill_rq (TYPE_3__*,struct request*) ; 
 int /*<<< orphan*/  ide_stopped ; 
 int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ide_startstop_t ide_atapi_error(ide_drive_t *drive, struct request *rq,
				       u8 stat, u8 err)
{
	ide_hwif_t *hwif = drive->hwif;

	if ((stat & ATA_BUSY) ||
	    ((stat & ATA_DF) && (drive->dev_flags & IDE_DFLAG_NOWERR) == 0)) {
		/* other bits are useless when BUSY */
		rq->errors |= ERROR_RESET;
	} else {
		/* add decoding error stuff */
	}

	if (hwif->tp_ops->read_status(hwif) & (ATA_BUSY | ATA_DRQ))
		/* force an abort */
		hwif->tp_ops->exec_command(hwif, ATA_CMD_IDLEIMMEDIATE);

	if (rq->errors >= ERROR_MAX) {
		ide_kill_rq(drive, rq);
	} else {
		if ((rq->errors & ERROR_RESET) == ERROR_RESET) {
			++rq->errors;
			return ide_do_reset(drive);
		}
		++rq->errors;
	}

	return ide_stopped;
}