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
typedef  int uint64_t ;
struct device {int /*<<< orphan*/ * bus; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_2__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 unsigned long BAR2_PCI_ADDRESS ; 
 int /*<<< orphan*/  CVMX_NPI_PCI_BAR1_INDEXX (int) ; 
#define  OCTEON_DMA_BAR_TYPE_BIG 130 
#define  OCTEON_DMA_BAR_TYPE_PCIE 129 
#define  OCTEON_DMA_BAR_TYPE_SMALL 128 
 int OCTEON_PCI_BAR1_HOLE_SIZE ; 
 int /*<<< orphan*/  bar1_lock ; 
 TYPE_1__* bar1_state ; 
 int octeon_dma_bar_type ; 
 int /*<<< orphan*/  octeon_npi_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void octeon_unmap_dma_mem(struct device *dev, dma_addr_t dma_addr)
{
#ifndef CONFIG_PCI
	/*
	 * Without PCI/PCIe this function can be called for Octeon internal
	 * devices such as USB. These devices all support 64bit addressing.
	 */
	return;
#else
	unsigned long flags;
	uint64_t index;

	/*
	 * Platform devices, such as the internal USB, skip all
	 * translation and use Octeon physical addresses directly.
	 */
	if (dev->bus == &platform_bus_type)
		return;

	switch (octeon_dma_bar_type) {
	case OCTEON_DMA_BAR_TYPE_PCIE:
		/* Nothing to do, all mappings are static */
		goto done;

	case OCTEON_DMA_BAR_TYPE_BIG:
#ifdef CONFIG_64BIT
		/* Nothing to do for addresses using BAR2 */
		if (dma_addr >= BAR2_PCI_ADDRESS)
			goto done;
#endif
		if (unlikely(dma_addr < (4ul << 10)))
			panic("dma_unmap_single: Unexpect DMA address 0x%llx\n",
			      dma_addr);
		else if (dma_addr < (2ul << 30))
			/* Nothing to do for addresses using BAR0 */
			goto done;
		else if (dma_addr < (2ul << 30) + (128ul << 20))
			/* Need to unmap, fall through */
			index = (dma_addr - (2ul << 30)) >> 22;
		else if (dma_addr <
			 (4ul << 30) - (OCTEON_PCI_BAR1_HOLE_SIZE << 20))
			goto done;	/* Nothing to do for the rest of BAR1 */
		else
			panic("dma_unmap_single: Unexpect DMA address 0x%llx\n",
			      dma_addr);
		/* Continued below switch statement */
		break;

	case OCTEON_DMA_BAR_TYPE_SMALL:
#ifdef CONFIG_64BIT
		/* Nothing to do for addresses using BAR2 */
		if (dma_addr >= BAR2_PCI_ADDRESS)
			goto done;
#endif
		index = dma_addr >> 22;
		/* Continued below switch statement */
		break;

	default:
		panic("dma_unmap_single: Invalid octeon_dma_bar_type\n");
	}

	if (unlikely(index > 31))
		panic("dma_unmap_single: "
		      "Attempt to unmap an invalid address (0x%llx)\n",
		      dma_addr);

	spin_lock_irqsave(&bar1_lock, flags);
	bar1_state[index].ref_count--;
	if (bar1_state[index].ref_count == 0)
		octeon_npi_write32(CVMX_NPI_PCI_BAR1_INDEXX(index), 0);
	else if (unlikely(bar1_state[index].ref_count < 0))
		panic("dma_unmap_single: Bar1[%u] reference count < 0\n",
		      (int) index);
	spin_unlock_irqrestore(&bar1_lock, flags);
done:
	pr_debug("dma_unmap_single 0x%llx\n", dma_addr);
	return;
#endif
}