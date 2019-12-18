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
struct TYPE_2__ {int csr; unsigned short fifo_count; int bpack_lo; int bpack_hi; scalar_t__ fifo_count_hi; scalar_t__ dma_count_lo; scalar_t__ dma_count_hi; scalar_t__ dma_addr_lo; scalar_t__ dma_addr_hi; } ;

/* Variables and functions */
 int CSR_DMA_ENABLE ; 
 int CSR_FIFO ; 
 int CSR_LEFT ; 
#define  CSR_LEFT_1 130 
#define  CSR_LEFT_2 129 
#define  CSR_LEFT_3 128 
 int CSR_SEND ; 
 TYPE_1__* dregs ; 
 int /*<<< orphan*/  dvma_unmap (int /*<<< orphan*/ *) ; 
 scalar_t__ dvma_vmetov (int /*<<< orphan*/ *) ; 
 unsigned short last_residual ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ sun3_dma_active ; 
 int /*<<< orphan*/ * sun3_dma_orig_addr ; 
 unsigned short sun3_dma_orig_count ; 
 int /*<<< orphan*/ * sun3_dma_setup_done ; 

__attribute__((used)) static int sun3scsi_dma_finish(int write_flag)
{
	unsigned short fifo;
	int ret = 0;
	
	sun3_dma_active = 0;

	dregs->csr &= ~CSR_DMA_ENABLE;
	
	fifo = dregs->fifo_count;
	if(write_flag) {
		if((fifo > 0) && (fifo < sun3_dma_orig_count))
			fifo++;
	}

	last_residual = fifo;
#ifdef SUN3_SCSI_DEBUG
	printk("scsi: residual %x total %x\n", fifo, sun3_dma_orig_count);
#endif
	/* empty bytes from the fifo which didn't make it */
	if((!write_flag) && (dregs->csr & CSR_LEFT)) {
		unsigned char *vaddr;

#ifdef SUN3_SCSI_DEBUG
		printk("scsi: got left over bytes\n");
#endif

		vaddr = (unsigned char *)dvma_vmetov(sun3_dma_orig_addr);
		
		vaddr += (sun3_dma_orig_count - fifo);
		vaddr--;
		
		switch(dregs->csr & CSR_LEFT) {
		case CSR_LEFT_3:
			*vaddr = (dregs->bpack_lo & 0xff00) >> 8;
			vaddr--;
			
		case CSR_LEFT_2:
			*vaddr = (dregs->bpack_hi & 0x00ff);
			vaddr--;
			
		case CSR_LEFT_1:
			*vaddr = (dregs->bpack_hi & 0xff00) >> 8;
			break;
		}
		
		
	}

	dvma_unmap(sun3_dma_orig_addr);
	sun3_dma_orig_addr = NULL;

	dregs->dma_addr_hi = 0;
	dregs->dma_addr_lo = 0;
	dregs->dma_count_hi = 0;
	dregs->dma_count_lo = 0;

	dregs->fifo_count = 0;
	dregs->fifo_count_hi = 0;

	dregs->csr &= ~CSR_SEND;
	
//	dregs->csr |= CSR_DMA_ENABLE;
	
#if 0
	/* reset fifo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
#endif	
	sun3_dma_setup_done = NULL;

	return ret;

}