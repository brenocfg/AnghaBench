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
struct TYPE_2__ {unsigned long dma_addr_hi; unsigned long dma_addr_lo; int /*<<< orphan*/  csr; scalar_t__ fifo_count; scalar_t__ fifo_count_hi; scalar_t__ dma_count_lo; scalar_t__ dma_count_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_FIFO ; 
 int /*<<< orphan*/  CSR_PACK_ENABLE ; 
 int /*<<< orphan*/  CSR_SEND ; 
 TYPE_1__* dregs ; 
 scalar_t__ dvma_map_vme (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dvma_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,void*,...) ; 
 int /*<<< orphan*/ * sun3_dma_orig_addr ; 
 unsigned long sun3_dma_orig_count ; 

__attribute__((used)) static unsigned long sun3scsi_dma_setup(void *data, unsigned long count, int write_flag)
{
	void *addr;

	if(sun3_dma_orig_addr != NULL)
		dvma_unmap(sun3_dma_orig_addr);

//	addr = sun3_dvma_page((unsigned long)data, (unsigned long)dmabuf);
	addr = (void *)dvma_map_vme((unsigned long) data, count);
		
	sun3_dma_orig_addr = addr;
	sun3_dma_orig_count = count;
	
#ifdef SUN3_SCSI_DEBUG
	printk("scsi: dma_setup addr %p count %x\n", addr, count);
#endif

//	dregs->fifo_count = 0;
#if 0	
	/* reset fifo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
#endif	
	/* set direction */
	if(write_flag)
		dregs->csr |= CSR_SEND;
	else
		dregs->csr &= ~CSR_SEND;
	
	/* reset fifo */
//	dregs->csr &= ~CSR_FIFO;
//	dregs->csr |= CSR_FIFO;

	dregs->csr |= CSR_PACK_ENABLE;

	dregs->dma_addr_hi = ((unsigned long)addr >> 16);
	dregs->dma_addr_lo = ((unsigned long)addr & 0xffff);
	
	dregs->dma_count_hi = 0;
	dregs->dma_count_lo = 0;
	dregs->fifo_count_hi = 0;
	dregs->fifo_count = 0;
		
#ifdef SUN3_SCSI_DEBUG
	printk("scsi: dma_setup done csr %x\n", dregs->csr);
#endif
       	return count;

}