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
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 struct pci_dev* alloc_pci_dev () ; 
 int /*<<< orphan*/  kfree_pci_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  memcpy (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
make_local_pdev(adapter_t *adapter, struct pci_dev **pdev)
{
	*pdev = alloc_pci_dev();

	if( *pdev == NULL ) return -1;

	memcpy(*pdev, adapter->dev, sizeof(struct pci_dev));

	if( pci_set_dma_mask(*pdev, DMA_BIT_MASK(32)) != 0 ) {
		kfree_pci_dev(*pdev);
		return -1;
	}

	return 0;
}