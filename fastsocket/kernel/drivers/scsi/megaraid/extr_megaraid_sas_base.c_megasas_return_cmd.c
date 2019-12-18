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
struct megasas_instance {int /*<<< orphan*/  cmd_pool_lock; int /*<<< orphan*/  cmd_pool; TYPE_1__* pdev; } ;
struct megasas_cmd {int /*<<< orphan*/  list; TYPE_3__* frame; scalar_t__ frame_count; int /*<<< orphan*/ * scmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
struct TYPE_4__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_CMD_INVALID ; 
 scalar_t__ PCI_DEVICE_ID_LSI_FURY ; 
 scalar_t__ PCI_DEVICE_ID_LSI_FUSION ; 
 scalar_t__ PCI_DEVICE_ID_LSI_INVADER ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ reset_devices ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

inline void
megasas_return_cmd(struct megasas_instance *instance, struct megasas_cmd *cmd)
{
	unsigned long flags;

	spin_lock_irqsave(&instance->cmd_pool_lock, flags);

	cmd->scmd = NULL;
	cmd->frame_count = 0;
	if ((instance->pdev->device != PCI_DEVICE_ID_LSI_FUSION) &&
	    (instance->pdev->device != PCI_DEVICE_ID_LSI_INVADER) &&
	    (instance->pdev->device != PCI_DEVICE_ID_LSI_FURY) &&
	    (reset_devices))
		cmd->frame->hdr.cmd = MFI_CMD_INVALID;
	list_add_tail(&cmd->list, &instance->cmd_pool);

	spin_unlock_irqrestore(&instance->cmd_pool_lock, flags);
}