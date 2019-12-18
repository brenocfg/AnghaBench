#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ctlr_info {TYPE_2__* pdev; } ;
struct CommandList {TYPE_1__* err_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ CommandStatus; scalar_t__ ScsiStatus; scalar_t__* SenseInfo; } ;

/* Variables and functions */
 scalar_t__ CMD_SUCCESS ; 
 scalar_t__ CMD_TARGET_STATUS ; 
 int HPSA_MAX_WAIT_INTERVAL_SECS ; 
 int HPSA_TUR_RETRY_LIMIT ; 
 int IO_ERROR ; 
 scalar_t__ NO_SENSE ; 
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  TEST_UNIT_READY ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 scalar_t__ UNIT_ATTENTION ; 
 struct CommandList* cmd_special_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_special_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_do_simple_cmd_core (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int wait_for_device_to_become_ready(struct ctlr_info *h,
	unsigned char lunaddr[])
{
	int rc = 0;
	int count = 0;
	int waittime = 1; /* seconds */
	struct CommandList *c;

	c = cmd_special_alloc(h);
	if (!c) {
		dev_warn(&h->pdev->dev, "out of memory in "
			"wait_for_device_to_become_ready.\n");
		return IO_ERROR;
	}

	/* Send test unit ready until device ready, or give up. */
	while (count < HPSA_TUR_RETRY_LIMIT) {

		/* Wait for a bit.  do this first, because if we send
		 * the TUR right away, the reset will just abort it.
		 */
		msleep(1000 * waittime);
		count++;

		/* Increase wait time with each try, up to a point. */
		if (waittime < HPSA_MAX_WAIT_INTERVAL_SECS)
			waittime = waittime * 2;

		/* Send the Test Unit Ready */
		fill_cmd(c, TEST_UNIT_READY, h, NULL, 0, 0, lunaddr, TYPE_CMD);
		hpsa_scsi_do_simple_cmd_core(h, c);
		/* no unmap needed here because no data xfer. */

		if (c->err_info->CommandStatus == CMD_SUCCESS)
			break;

		if (c->err_info->CommandStatus == CMD_TARGET_STATUS &&
			c->err_info->ScsiStatus == SAM_STAT_CHECK_CONDITION &&
			(c->err_info->SenseInfo[2] == NO_SENSE ||
			c->err_info->SenseInfo[2] == UNIT_ATTENTION))
			break;

		dev_warn(&h->pdev->dev, "waiting %d secs "
			"for device to become ready.\n", waittime);
		rc = 1; /* device not ready. */
	}

	if (rc)
		dev_warn(&h->pdev->dev, "giving up on device.\n");
	else
		dev_warn(&h->pdev->dev, "device is ready.\n");

	cmd_special_free(h, c);
	return rc;
}