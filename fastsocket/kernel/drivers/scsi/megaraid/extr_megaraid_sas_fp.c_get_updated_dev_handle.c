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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct LD_LOAD_BALANCE_INFO {int /*<<< orphan*/ * scsi_pending_cmds; int /*<<< orphan*/ * raid1DevHandle; } ;
struct IO_REQUEST_INFO {int /*<<< orphan*/  numBlocks; int /*<<< orphan*/  ldStartBlock; int /*<<< orphan*/  devHandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 size_t megasas_get_best_arm (struct LD_LOAD_BALANCE_INFO*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 get_updated_dev_handle(struct LD_LOAD_BALANCE_INFO *lbInfo,
			   struct IO_REQUEST_INFO *io_info)
{
	u8 arm, old_arm;
	u16 devHandle;

	old_arm = lbInfo->raid1DevHandle[0] == io_info->devHandle ? 0 : 1;

	/* get best new arm */
	arm  = megasas_get_best_arm(lbInfo, old_arm, io_info->ldStartBlock,
				    io_info->numBlocks);
	devHandle = lbInfo->raid1DevHandle[arm];
	atomic_inc(&lbInfo->scsi_pending_cmds[arm]);

	return devHandle;
}