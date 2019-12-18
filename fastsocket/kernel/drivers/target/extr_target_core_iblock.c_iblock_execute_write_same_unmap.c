#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct se_cmd {int /*<<< orphan*/  t_task_lba; int /*<<< orphan*/  se_dev; } ;
struct iblock_dev {int /*<<< orphan*/  ibd_bd; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOOD ; 
 struct iblock_dev* IBLOCK_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int blkdev_issue_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  sbc_get_write_same_sectors (struct se_cmd*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sense_reason_t
iblock_execute_write_same_unmap(struct se_cmd *cmd)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(cmd->se_dev);
	int rc;

	rc = blkdev_issue_discard(ib_dev->ibd_bd, cmd->t_task_lba,
			sbc_get_write_same_sectors(cmd), GFP_KERNEL, 0);
	if (rc < 0) {
		pr_warn("blkdev_issue_discard() failed: %d\n", rc);
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	target_complete_cmd(cmd, GOOD);
	return 0;
}