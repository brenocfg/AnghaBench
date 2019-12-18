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
struct sbp2_lu {int /*<<< orphan*/  cmd_orb_completed; TYPE_3__* hi; } ;
struct sbp2_command_orb {int dummy; } ;
struct sbp2_command_info {void* command_orb_dma; int /*<<< orphan*/  list; void* sge_dma; int /*<<< orphan*/  scatter_gather_element; int /*<<< orphan*/  command_orb; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* host; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SBP2_MAX_CMDS ; 
 void* dma_map_single (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sbp2_command_info*) ; 
 struct sbp2_command_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sbp2_serialize_io ; 

__attribute__((used)) static int sbp2util_create_command_orb_pool(struct sbp2_lu *lu)
{
	struct sbp2_command_info *cmd;
	struct device *dmadev = lu->hi->host->device.parent;
	int i, orbs = sbp2_serialize_io ? 2 : SBP2_MAX_CMDS;

	for (i = 0; i < orbs; i++) {
		cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
		if (!cmd)
			goto failed_alloc;

		cmd->command_orb_dma =
		    dma_map_single(dmadev, &cmd->command_orb,
				   sizeof(struct sbp2_command_orb),
				   DMA_TO_DEVICE);
		if (dma_mapping_error(dmadev, cmd->command_orb_dma))
			goto failed_orb;

		cmd->sge_dma =
		    dma_map_single(dmadev, &cmd->scatter_gather_element,
				   sizeof(cmd->scatter_gather_element),
				   DMA_TO_DEVICE);
		if (dma_mapping_error(dmadev, cmd->sge_dma))
			goto failed_sge;

		INIT_LIST_HEAD(&cmd->list);
		list_add_tail(&cmd->list, &lu->cmd_orb_completed);
	}
	return 0;

failed_sge:
	dma_unmap_single(dmadev, cmd->command_orb_dma,
			 sizeof(struct sbp2_command_orb), DMA_TO_DEVICE);
failed_orb:
	kfree(cmd);
failed_alloc:
	return -ENOMEM;
}