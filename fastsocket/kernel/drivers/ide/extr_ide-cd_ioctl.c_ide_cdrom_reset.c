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
struct request_sense {int dummy; } ;
struct request {int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  cmd_type; } ;
struct cdrom_info {int /*<<< orphan*/  disk; } ;
struct cdrom_device_info {TYPE_1__* handle; } ;
struct TYPE_3__ {int atapi_flags; int /*<<< orphan*/  queue; struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int IDE_AFLAG_DOOR_LOCKED ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_QUIET ; 
 int /*<<< orphan*/  REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  ide_cd_lockdoor (TYPE_1__*,int,struct request_sense*) ; 

int ide_cdrom_reset(struct cdrom_device_info *cdi)
{
	ide_drive_t *drive = cdi->handle;
	struct cdrom_info *cd = drive->driver_data;
	struct request_sense sense;
	struct request *rq;
	int ret;

	rq = blk_get_request(drive->queue, READ, __GFP_WAIT);
	rq->cmd_type = REQ_TYPE_SPECIAL;
	rq->cmd_flags = REQ_QUIET;
	ret = blk_execute_rq(drive->queue, cd->disk, rq, 0);
	blk_put_request(rq);
	/*
	 * A reset will unlock the door. If it was previously locked,
	 * lock it again.
	 */
	if (drive->atapi_flags & IDE_AFLAG_DOOR_LOCKED)
		(void)ide_cd_lockdoor(drive, 1, &sense);

	return ret;
}