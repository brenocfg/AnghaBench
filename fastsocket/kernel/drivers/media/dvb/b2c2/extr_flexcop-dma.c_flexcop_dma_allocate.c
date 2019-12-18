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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct flexcop_dma {int size; void* dma_addr1; int /*<<< orphan*/ * cpu_addr1; void* dma_addr0; int /*<<< orphan*/ * cpu_addr0; struct pci_dev* pdev; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (struct pci_dev*,int,void**) ; 

int flexcop_dma_allocate(struct pci_dev *pdev,
		struct flexcop_dma *dma, u32 size)
{
	u8 *tcpu;
	dma_addr_t tdma = 0;

	if (size % 2) {
		err("dma buffersize has to be even.");
		return -EINVAL;
	}

	if ((tcpu = pci_alloc_consistent(pdev, size, &tdma)) != NULL) {
		dma->pdev = pdev;
		dma->cpu_addr0 = tcpu;
		dma->dma_addr0 = tdma;
		dma->cpu_addr1 = tcpu + size/2;
		dma->dma_addr1 = tdma + size/2;
		dma->size = size/2;
		return 0;
	}
	return -ENOMEM;
}