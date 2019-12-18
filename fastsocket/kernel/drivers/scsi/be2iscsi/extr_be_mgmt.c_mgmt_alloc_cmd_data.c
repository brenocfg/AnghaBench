#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct beiscsi_hba {TYPE_1__ ctrl; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  va; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mgmt_alloc_cmd_data(struct beiscsi_hba *phba, struct be_dma_mem *cmd,
			       int iscsi_cmd, int size)
{
	cmd->va = pci_alloc_consistent(phba->ctrl.pdev, size, &cmd->dma);
	if (!cmd->va) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BG_%d : Failed to allocate memory for if info\n");
		return -ENOMEM;
	}
	memset(cmd->va, 0, size);
	cmd->size = size;
	be_cmd_hdr_prepare(cmd->va, CMD_SUBSYSTEM_ISCSI, iscsi_cmd, size);
	return 0;
}