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
typedef  int u32 ;
struct megasas_instance {int max_mfi_cmds; int /*<<< orphan*/ * sense_dma_pool; int /*<<< orphan*/ * frame_dma_pool; struct megasas_cmd** cmd_list; } ;
struct megasas_cmd {int /*<<< orphan*/  sense_phys_addr; scalar_t__ sense; int /*<<< orphan*/  frame_phys_addr; scalar_t__ frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void megasas_teardown_frame_pool(struct megasas_instance *instance)
{
	int i;
	u32 max_cmd = instance->max_mfi_cmds;
	struct megasas_cmd *cmd;

	if (!instance->frame_dma_pool)
		return;

	/*
	 * Return all frames to pool
	 */
	for (i = 0; i < max_cmd; i++) {

		cmd = instance->cmd_list[i];

		if (cmd->frame)
			pci_pool_free(instance->frame_dma_pool, cmd->frame,
				      cmd->frame_phys_addr);

		if (cmd->sense)
			pci_pool_free(instance->sense_dma_pool, cmd->sense,
				      cmd->sense_phys_addr);
	}

	/*
	 * Now destroy the pool itself
	 */
	pci_pool_destroy(instance->frame_dma_pool);
	pci_pool_destroy(instance->sense_dma_pool);

	instance->frame_dma_pool = NULL;
	instance->sense_dma_pool = NULL;
}