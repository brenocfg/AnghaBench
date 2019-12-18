#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct request_pm_state {int /*<<< orphan*/  pm_state; int /*<<< orphan*/  pm_step; } ;
struct request {struct request_pm_state* special; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  cmd_type; } ;
struct ide_driver {int /*<<< orphan*/  (* resume ) (TYPE_1__*) ;} ;
struct device {scalar_t__ driver; } ;
typedef  int /*<<< orphan*/  rqpm ;
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_7__ {int dn; int /*<<< orphan*/  queue; int /*<<< orphan*/ * hwif; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_PM_START_RESUME ; 
 int /*<<< orphan*/  PM_EVENT_ON ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_PREEMPT ; 
 int /*<<< orphan*/  REQ_TYPE_PM_RESUME ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 TYPE_1__* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ide_acpi_exec_tfs (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_acpi_push_timing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_acpi_set_state (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ide_get_pair_dev (TYPE_1__*) ; 
 scalar_t__ ide_port_acpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct request_pm_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct ide_driver* to_ide_driver (scalar_t__) ; 

int generic_ide_resume(struct device *dev)
{
	ide_drive_t *drive = dev_get_drvdata(dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	ide_hwif_t *hwif = drive->hwif;
	struct request *rq;
	struct request_pm_state rqpm;
	int err;

	if (ide_port_acpi(hwif)) {
		/* call ACPI _PS0 / _STM only once */
		if ((drive->dn & 1) == 0 || pair == NULL) {
			ide_acpi_set_state(hwif, 1);
			ide_acpi_push_timing(hwif);
		}

		ide_acpi_exec_tfs(drive);
	}

	memset(&rqpm, 0, sizeof(rqpm));
	rq = blk_get_request(drive->queue, READ, __GFP_WAIT);
	rq->cmd_type = REQ_TYPE_PM_RESUME;
	rq->cmd_flags |= REQ_PREEMPT;
	rq->special = &rqpm;
	rqpm.pm_step = IDE_PM_START_RESUME;
	rqpm.pm_state = PM_EVENT_ON;

	err = blk_execute_rq(drive->queue, NULL, rq, 1);
	blk_put_request(rq);

	if (err == 0 && dev->driver) {
		struct ide_driver *drv = to_ide_driver(dev->driver);

		if (drv->resume)
			drv->resume(drive);
	}

	return err;
}