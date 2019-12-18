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
struct pci_dev {int dummy; } ;
struct dma_loaf {size_t length; int /*<<< orphan*/  dma_base; int /*<<< orphan*/  dma_free; void* cpu_base; void* cpu_free; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* pci_alloc_consistent (struct pci_dev*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool init_dma_loaf(struct pci_dev *dev, struct dma_loaf *loaf,
								 size_t len)
{
	void *cpu_addr;
	dma_addr_t dma_handle;

	cpu_addr = pci_alloc_consistent(dev, len, &dma_handle);
	if (cpu_addr == NULL)
		return false;
	
	loaf->cpu_free = loaf->cpu_base = cpu_addr;
	loaf->dma_free =loaf->dma_base = dma_handle;
	loaf->length = len;
	memset(cpu_addr, 0, len);
	return true;
}