#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct be_mcc_mailbox {int dummy; } ;
struct be_dma_mem {int size; int /*<<< orphan*/ * dma; int /*<<< orphan*/ * va; } ;
struct be_cmd_req_rx_filter {int dummy; } ;
struct be_adapter {int sli_family; int virtfn; TYPE_1__* pdev; int /*<<< orphan*/  flash_compl; int /*<<< orphan*/  mcc_cq_lock; int /*<<< orphan*/  mcc_lock; int /*<<< orphan*/  mbox_lock; struct be_dma_mem rx_filter; struct be_dma_mem mbox_mem; struct be_dma_mem mbox_mem_alloced; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 void* PTR_ALIGN (int /*<<< orphan*/ *,int) ; 
 int SLI_INTF_FAMILY_MASK ; 
 int SLI_INTF_FAMILY_SHIFT ; 
 int SLI_INTF_FT_MASK ; 
 int /*<<< orphan*/  SLI_INTF_REG_OFFSET ; 
 int __GFP_ZERO ; 
 int be_map_pci_bars (struct be_adapter*) ; 
 int /*<<< orphan*/  be_unmap_pci_bars (struct be_adapter*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_save_state (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int be_ctrl_init(struct be_adapter *adapter)
{
	struct be_dma_mem *mbox_mem_alloc = &adapter->mbox_mem_alloced;
	struct be_dma_mem *mbox_mem_align = &adapter->mbox_mem;
	struct be_dma_mem *rx_filter = &adapter->rx_filter;
	u32 sli_intf;
	int status;

	pci_read_config_dword(adapter->pdev, SLI_INTF_REG_OFFSET, &sli_intf);
	adapter->sli_family = (sli_intf & SLI_INTF_FAMILY_MASK) >>
				 SLI_INTF_FAMILY_SHIFT;
	adapter->virtfn = (sli_intf & SLI_INTF_FT_MASK) ? 1 : 0;

	status = be_map_pci_bars(adapter);
	if (status)
		goto done;

	mbox_mem_alloc->size = sizeof(struct be_mcc_mailbox) + 16;
	mbox_mem_alloc->va = dma_alloc_coherent(&adapter->pdev->dev,
						mbox_mem_alloc->size,
						&mbox_mem_alloc->dma,
						GFP_KERNEL);
	if (!mbox_mem_alloc->va) {
		status = -ENOMEM;
		goto unmap_pci_bars;
	}
	mbox_mem_align->size = sizeof(struct be_mcc_mailbox);
	mbox_mem_align->va = PTR_ALIGN(mbox_mem_alloc->va, 16);
	mbox_mem_align->dma = PTR_ALIGN(mbox_mem_alloc->dma, 16);
	memset(mbox_mem_align->va, 0, sizeof(struct be_mcc_mailbox));

	rx_filter->size = sizeof(struct be_cmd_req_rx_filter);
	rx_filter->va = dma_alloc_coherent(&adapter->pdev->dev, rx_filter->size,
					   &rx_filter->dma,
					   GFP_KERNEL | __GFP_ZERO);
	if (rx_filter->va == NULL) {
		status = -ENOMEM;
		goto free_mbox;
	}

	mutex_init(&adapter->mbox_lock);
	spin_lock_init(&adapter->mcc_lock);
	spin_lock_init(&adapter->mcc_cq_lock);

	init_completion(&adapter->flash_compl);
	pci_save_state(adapter->pdev);
	return 0;

free_mbox:
	dma_free_coherent(&adapter->pdev->dev, mbox_mem_alloc->size,
			  mbox_mem_alloc->va, mbox_mem_alloc->dma);

unmap_pci_bars:
	be_unmap_pci_bars(adapter);

done:
	return status;
}