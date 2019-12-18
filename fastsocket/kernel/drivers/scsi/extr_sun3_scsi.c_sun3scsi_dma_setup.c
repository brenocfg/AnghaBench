#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ addr ;
struct TYPE_10__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_9__ {unsigned long fifo_count; int /*<<< orphan*/  csr; } ;
struct TYPE_8__ {int addr_hi; int addr_lo; unsigned long count; int /*<<< orphan*/  rsel; int /*<<< orphan*/  mode_lo; int /*<<< orphan*/  mode_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_FIFO ; 
 int /*<<< orphan*/  CSR_SEND ; 
 int /*<<< orphan*/  NCR5380_print (TYPE_6__*) ; 
 int /*<<< orphan*/  UDC_CHN_HI ; 
 int /*<<< orphan*/  UDC_CHN_LO ; 
 int /*<<< orphan*/  UDC_CSR ; 
 int UDC_INT_ENABLE ; 
 int /*<<< orphan*/  UDC_MODE ; 
 int /*<<< orphan*/  UDC_MODE_HIWORD ; 
 int /*<<< orphan*/  UDC_MODE_LRECV ; 
 int /*<<< orphan*/  UDC_MODE_LSEND ; 
 int UDC_RESET ; 
 int /*<<< orphan*/  UDC_RSEL_RECV ; 
 int /*<<< orphan*/  UDC_RSEL_SEND ; 
 TYPE_6__* default_instance ; 
 TYPE_1__* dmabuf ; 
 TYPE_4__* dregs ; 
 scalar_t__ dvma_map (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dvma_unmap (int /*<<< orphan*/ *) ; 
 int dvma_vtob (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,void*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int /*<<< orphan*/ * sun3_dma_orig_addr ; 
 unsigned long sun3_dma_orig_count ; 
 int /*<<< orphan*/  sun3_udc_write (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* udc_regs ; 

__attribute__((used)) static unsigned long sun3scsi_dma_setup(void *data, unsigned long count, int write_flag)
{
#ifdef OLDDMA
	if(write_flag) 
		memcpy(dmabuf, data, count);
	else {
		sun3_dma_orig_addr = data;
		sun3_dma_orig_count = count;
	}
#else
	void *addr;

	if(sun3_dma_orig_addr != NULL)
		dvma_unmap(sun3_dma_orig_addr);

//	addr = sun3_dvma_page((unsigned long)data, (unsigned long)dmabuf);
	addr = (void *)dvma_map((unsigned long) data, count);
		
	sun3_dma_orig_addr = addr;
	sun3_dma_orig_count = count;
#endif
	dregs->fifo_count = 0;
	sun3_udc_write(UDC_RESET, UDC_CSR);
	
	/* reset fifo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
	
	/* set direction */
	if(write_flag)
		dregs->csr |= CSR_SEND;
	else
		dregs->csr &= ~CSR_SEND;
	
	/* byte count for fifo */
	dregs->fifo_count = count;

	sun3_udc_write(UDC_RESET, UDC_CSR);
	
	/* reset fifo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
	
	if(dregs->fifo_count != count) { 
		printk("scsi%d: fifo_mismatch %04x not %04x\n",
		       default_instance->host_no, dregs->fifo_count,
		       (unsigned int) count);
		NCR5380_print(default_instance);
	}

	/* setup udc */
#ifdef OLDDMA
	udc_regs->addr_hi = ((dvma_vtob(dmabuf) & 0xff0000) >> 8);
	udc_regs->addr_lo = (dvma_vtob(dmabuf) & 0xffff);
#else
	udc_regs->addr_hi = (((unsigned long)(addr) & 0xff0000) >> 8);
	udc_regs->addr_lo = ((unsigned long)(addr) & 0xffff);
#endif
	udc_regs->count = count/2; /* count in words */
	udc_regs->mode_hi = UDC_MODE_HIWORD;
	if(write_flag) {
		if(count & 1)
			udc_regs->count++;
		udc_regs->mode_lo = UDC_MODE_LSEND;
		udc_regs->rsel = UDC_RSEL_SEND;
	} else {
		udc_regs->mode_lo = UDC_MODE_LRECV;
		udc_regs->rsel = UDC_RSEL_RECV;
	}
	
	/* announce location of regs block */
	sun3_udc_write(((dvma_vtob(udc_regs) & 0xff0000) >> 8),
		       UDC_CHN_HI); 

	sun3_udc_write((dvma_vtob(udc_regs) & 0xffff), UDC_CHN_LO);

	/* set dma master on */
	sun3_udc_write(0xd, UDC_MODE);

	/* interrupt enable */
	sun3_udc_write(UDC_INT_ENABLE, UDC_CSR);
	
       	return count;

}