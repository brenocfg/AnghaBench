#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int block_size; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
struct se_cmd {int* t_task_cdb; int t_task_lba; scalar_t__ data_length; struct se_device* se_dev; } ;
struct fd_dev {TYPE_3__* fd_file; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int loff_t ;
struct TYPE_5__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_6__ {TYPE_2__ f_path; } ;

/* Variables and functions */
 struct fd_dev* FD_DEV (struct se_device*) ; 
 int LLONG_MAX ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int vfs_fsync_range (TYPE_3__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static sense_reason_t
fd_execute_sync_cache(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct fd_dev *fd_dev = FD_DEV(dev);
	int immed = (cmd->t_task_cdb[1] & 0x2);
	loff_t start, end;
	int ret;

	/*
	 * If the Immediate bit is set, queue up the GOOD response
	 * for this SYNCHRONIZE_CACHE op
	 */
	if (immed)
		target_complete_cmd(cmd, SAM_STAT_GOOD);

	/*
	 * Determine if we will be flushing the entire device.
	 */
	if (cmd->t_task_lba == 0 && cmd->data_length == 0) {
		start = 0;
		end = LLONG_MAX;
	} else {
		start = cmd->t_task_lba * dev->dev_attrib.block_size;
		if (cmd->data_length)
			end = start + cmd->data_length;
		else
			end = LLONG_MAX;
	}

	ret = vfs_fsync_range(fd_dev->fd_file, fd_dev->fd_file->f_path.dentry,
			      start, end, 1);
	if (ret != 0)
		pr_err("FILEIO: vfs_fsync_range() failed: %d\n", ret);

	if (immed)
		return 0;

	if (ret)
		target_complete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
	else
		target_complete_cmd(cmd, SAM_STAT_GOOD);

	return 0;
}