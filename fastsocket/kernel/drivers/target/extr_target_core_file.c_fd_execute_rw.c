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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ emulate_fua_write; int block_size; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
struct se_cmd {int data_direction; int se_cmd_flags; int t_task_lba; int data_length; struct se_device* se_dev; int /*<<< orphan*/  t_data_nents; struct scatterlist* t_data_sg; } ;
struct scatterlist {int dummy; } ;
struct fd_dev {TYPE_3__* fd_file; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int loff_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_5__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_6__ {TYPE_2__ f_path; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 struct fd_dev* FD_DEV (struct se_device*) ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int SCF_FUA ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int fd_do_rw (struct se_cmd*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_fsync_range (TYPE_3__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static sense_reason_t
fd_execute_rw(struct se_cmd *cmd)
{
	struct scatterlist *sgl = cmd->t_data_sg;
	u32 sgl_nents = cmd->t_data_nents;
	enum dma_data_direction data_direction = cmd->data_direction;
	struct se_device *dev = cmd->se_dev;
	int ret = 0;

	/*
	 * Call vectorized fileio functions to map struct scatterlist
	 * physical memory addresses to struct iovec virtual memory.
	 */
	if (data_direction == DMA_FROM_DEVICE) {
		ret = fd_do_rw(cmd, sgl, sgl_nents, 0);
	} else {
		ret = fd_do_rw(cmd, sgl, sgl_nents, 1);
		/*
		 * Perform implict vfs_fsync_range() for fd_do_writev() ops
		 * for SCSI WRITEs with Forced Unit Access (FUA) set.
		 * Allow this to happen independent of WCE=0 setting.
		 */
		if (ret > 0 &&
		    dev->dev_attrib.emulate_fua_write > 0 &&
		    (cmd->se_cmd_flags & SCF_FUA)) {
			struct fd_dev *fd_dev = FD_DEV(dev);
			loff_t start = cmd->t_task_lba *
				dev->dev_attrib.block_size;
			loff_t end = start + cmd->data_length;

			vfs_fsync_range(fd_dev->fd_file,
					fd_dev->fd_file->f_path.dentry,
					start, end, 1);
		}
	}

	if (ret < 0)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	if (ret)
		target_complete_cmd(cmd, SAM_STAT_GOOD);
	return 0;
}