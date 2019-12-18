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
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  csr; } ;
struct TYPE_3__ {int dma_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CSR_DMA_ENABLE ; 
 int /*<<< orphan*/  DMA_PRINTK (char*,int /*<<< orphan*/ ,char*,int,char*,unsigned char*) ; 
 int /*<<< orphan*/  HOSTNO ; 
 int ICR_ASSERT_DATA ; 
 int /*<<< orphan*/  INITIATOR_COMMAND_REG ; 
 int /*<<< orphan*/  MODE_REG ; 
 int MR_DMA_MODE ; 
 int MR_ENABLE_EOP_INTR ; 
 int NCR5380_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR5380_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESET_PARITY_INTERRUPT_REG ; 
 int /*<<< orphan*/  SETUP_HOSTDATA (struct Scsi_Host*) ; 
 unsigned char SR_IO ; 
 int /*<<< orphan*/  START_DMA_INITIATOR_RECEIVE_REG ; 
 int /*<<< orphan*/  START_DMA_SEND_REG ; 
 int /*<<< orphan*/  TARGET_COMMAND_REG ; 
 TYPE_2__* dregs ; 
 TYPE_1__* hostdata ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int sun3_dma_active ; 
 int /*<<< orphan*/  sun3_dma_setup_done ; 
 int /*<<< orphan*/  sun3scsi_dma_start (int,unsigned char*) ; 

__attribute__((used)) static int NCR5380_transfer_dma( struct Scsi_Host *instance, 
				 unsigned char *phase, int *count,
				 unsigned char **data)
{
    SETUP_HOSTDATA(instance);
    register int c = *count;
    register unsigned char p = *phase;
    unsigned long flags;

    /* sanity check */
    if(!sun3_dma_setup_done) {
	 printk("scsi%d: transfer_dma without setup!\n", HOSTNO);
	 BUG();
    }
    hostdata->dma_len = c;

    DMA_PRINTK("scsi%d: initializing DMA for %s, %d bytes %s %p\n",
	       HOSTNO, (p & SR_IO) ? "reading" : "writing",
	       c, (p & SR_IO) ? "to" : "from", *data);

    /* netbsd turns off ints here, why not be safe and do it too */
    local_irq_save(flags);
    
    /* send start chain */
    sun3scsi_dma_start(c, *data);
    
    if (p & SR_IO) {
	    NCR5380_write(TARGET_COMMAND_REG, 1);
	    NCR5380_read(RESET_PARITY_INTERRUPT_REG);
	    NCR5380_write(INITIATOR_COMMAND_REG, 0);
	    NCR5380_write(MODE_REG, (NCR5380_read(MODE_REG) | MR_DMA_MODE | MR_ENABLE_EOP_INTR));
	    NCR5380_write(START_DMA_INITIATOR_RECEIVE_REG, 0);
    } else {
	    NCR5380_write(TARGET_COMMAND_REG, 0);
	    NCR5380_read(RESET_PARITY_INTERRUPT_REG);
	    NCR5380_write(INITIATOR_COMMAND_REG, ICR_ASSERT_DATA);
	    NCR5380_write(MODE_REG, (NCR5380_read(MODE_REG) | MR_DMA_MODE | MR_ENABLE_EOP_INTR));
	    NCR5380_write(START_DMA_SEND_REG, 0);
    }

#ifdef SUN3_SCSI_VME
    dregs->csr |= CSR_DMA_ENABLE;
#endif

    local_irq_restore(flags);

    sun3_dma_active = 1;
    return 0;
}