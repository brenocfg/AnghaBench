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
struct request_pm_state {scalar_t__ pm_state; int /*<<< orphan*/  pm_step; } ;
struct request {struct request_pm_state* special; int /*<<< orphan*/  cmd_type; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  rqpm ;
struct TYPE_7__ {scalar_t__ event; } ;
typedef  TYPE_1__ pm_message_t ;
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_8__ {int dn; int /*<<< orphan*/  queue; int /*<<< orphan*/ * hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_PM_START_SUSPEND ; 
 scalar_t__ PM_EVENT_FREEZE ; 
 scalar_t__ PM_EVENT_PRETHAW ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_TYPE_PM_SUSPEND ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 TYPE_2__* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ide_acpi_get_timing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_acpi_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ide_get_pair_dev (TYPE_2__*) ; 
 scalar_t__ ide_port_acpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct request_pm_state*,int /*<<< orphan*/ ,int) ; 

int generic_ide_suspend(struct device *dev, pm_message_t mesg)
{
	ide_drive_t *drive = dev_get_drvdata(dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	ide_hwif_t *hwif = drive->hwif;
	struct request *rq;
	struct request_pm_state rqpm;
	int ret;

	if (ide_port_acpi(hwif)) {
		/* call ACPI _GTM only once */
		if ((drive->dn & 1) == 0 || pair == NULL)
			ide_acpi_get_timing(hwif);
	}

	memset(&rqpm, 0, sizeof(rqpm));
	rq = blk_get_request(drive->queue, READ, __GFP_WAIT);
	rq->cmd_type = REQ_TYPE_PM_SUSPEND;
	rq->special = &rqpm;
	rqpm.pm_step = IDE_PM_START_SUSPEND;
	if (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	rqpm.pm_state = mesg.event;

	ret = blk_execute_rq(drive->queue, NULL, rq, 0);
	blk_put_request(rq);

	if (ret == 0 && ide_port_acpi(hwif)) {
		/* call ACPI _PS3 only after both devices are suspended */
		if ((drive->dn & 1) || pair == NULL)
			ide_acpi_set_state(hwif, 0);
	}

	return ret;
}