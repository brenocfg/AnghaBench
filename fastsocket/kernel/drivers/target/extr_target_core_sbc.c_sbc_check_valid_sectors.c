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
typedef  unsigned long long u32 ;
struct TYPE_3__ {unsigned long long block_size; } ;
struct se_device {TYPE_2__* transport; TYPE_1__ dev_attrib; } ;
struct se_cmd {unsigned long long data_length; unsigned long long t_task_lba; struct se_device* se_dev; } ;
struct TYPE_4__ {int (* get_blocks ) (struct se_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long long,unsigned long long,unsigned long long) ; 
 int stub1 (struct se_device*) ; 

__attribute__((used)) static int sbc_check_valid_sectors(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	unsigned long long end_lba;
	u32 sectors;

	sectors = cmd->data_length / dev->dev_attrib.block_size;
	end_lba = dev->transport->get_blocks(dev) + 1;

	if (cmd->t_task_lba + sectors > end_lba) {
		pr_err("target: lba %llu, sectors %u exceeds end lba %llu\n",
			cmd->t_task_lba, sectors, end_lba);
		return -EINVAL;
	}

	return 0;
}