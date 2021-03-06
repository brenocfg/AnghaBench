#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request {scalar_t__ errors; struct ide_cmd* special; } ;
struct ide_cmd {scalar_t__ protocol; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATA_PROT_PIO ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  do_rw_taskfile (TYPE_1__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_init_sg_cmd (struct ide_cmd*,int) ; 
 int /*<<< orphan*/  ide_map_sg (TYPE_1__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_stopped ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ide_startstop_t execute_drive_cmd (ide_drive_t *drive,
		struct request *rq)
{
	struct ide_cmd *cmd = rq->special;

	if (cmd) {
		if (cmd->protocol == ATA_PROT_PIO) {
			ide_init_sg_cmd(cmd, blk_rq_sectors(rq) << 9);
			ide_map_sg(drive, cmd);
		}

		return do_rw_taskfile(drive, cmd);
	}

 	/*
 	 * NULL is actually a valid way of waiting for
 	 * all current requests to be flushed from the queue.
 	 */
#ifdef DEBUG
 	printk("%s: DRIVE_CMD (null)\n", drive->name);
#endif
	rq->errors = 0;
	ide_complete_rq(drive, 0, blk_rq_bytes(rq));

 	return ide_stopped;
}