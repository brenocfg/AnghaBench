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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocrdma_pbl {int dummy; } ;
struct ocrdma_hw_mr {int num_pbls; TYPE_2__* pbl_table; int /*<<< orphan*/  pbl_size; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  pa; void* va; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_free_mr_pbl_tbl (struct ocrdma_dev*,struct ocrdma_hw_mr*) ; 

__attribute__((used)) static int ocrdma_build_pbl_tbl(struct ocrdma_dev *dev, struct ocrdma_hw_mr *mr)
{
	int status = 0;
	int i;
	u32 dma_len = mr->pbl_size;
	struct pci_dev *pdev = dev->nic_info.pdev;
	void *va;
	dma_addr_t pa;

	mr->pbl_table = kzalloc(sizeof(struct ocrdma_pbl) *
				mr->num_pbls, GFP_KERNEL);

	if (!mr->pbl_table)
		return -ENOMEM;

	for (i = 0; i < mr->num_pbls; i++) {
		va = dma_alloc_coherent(&pdev->dev, dma_len, &pa, GFP_KERNEL);
		if (!va) {
			ocrdma_free_mr_pbl_tbl(dev, mr);
			status = -ENOMEM;
			break;
		}
		memset(va, 0, dma_len);
		mr->pbl_table[i].va = va;
		mr->pbl_table[i].pa = pa;
	}
	return status;
}