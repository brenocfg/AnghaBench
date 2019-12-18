#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned char volatile* SASR; unsigned char volatile* SCMD; } ;
typedef  TYPE_1__ wd33c93_regs ;
struct scsi_host_template {char* proc_name; int /*<<< orphan*/ * proc_info; } ;
struct WD33C93_hostdata {int dummy; } ;
struct TYPE_13__ {int no_sync; int /*<<< orphan*/  dma_mode; scalar_t__ fast; } ;
struct TYPE_12__ {int scsi_interrupt; int dma_cntrl; int dma_intr; } ;
struct TYPE_11__ {int base; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_DMA ; 
 TYPE_8__* HDATA (TYPE_2__*) ; 
 int /*<<< orphan*/  MACH_IS_MVME147 ; 
 int /*<<< orphan*/  MVME147_IRQ_SCSI_DMA ; 
 int /*<<< orphan*/  MVME147_IRQ_SCSI_PORT ; 
 int /*<<< orphan*/  WD33C93_FS_8_10 ; 
 int /*<<< orphan*/  dma_setup ; 
 int /*<<< orphan*/  dma_stop ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* m147_pcc ; 
 TYPE_2__* mvme147_host ; 
 int /*<<< orphan*/  mvme147_intr ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* scsi_register (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wd33c93_init (TYPE_2__*,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd33c93_proc_info ; 
 int /*<<< orphan*/  wd33c93_release () ; 

int mvme147_detect(struct scsi_host_template *tpnt)
{
    static unsigned char called = 0;
    wd33c93_regs regs;

    if (!MACH_IS_MVME147 || called)
	return 0;
    called++;

    tpnt->proc_name = "MVME147";
    tpnt->proc_info = &wd33c93_proc_info;

    mvme147_host = scsi_register (tpnt, sizeof(struct WD33C93_hostdata));
    if (!mvme147_host)
	    goto err_out;

    mvme147_host->base = 0xfffe4000;
    mvme147_host->irq = MVME147_IRQ_SCSI_PORT;
    regs.SASR = (volatile unsigned char *)0xfffe4000;
    regs.SCMD = (volatile unsigned char *)0xfffe4001;
    HDATA(mvme147_host)->no_sync = 0xff;
    HDATA(mvme147_host)->fast = 0;
    HDATA(mvme147_host)->dma_mode = CTRL_DMA;
    wd33c93_init(mvme147_host, regs, dma_setup, dma_stop, WD33C93_FS_8_10);

    if (request_irq(MVME147_IRQ_SCSI_PORT, mvme147_intr, 0, "MVME147 SCSI PORT", mvme147_intr))
	    goto err_unregister;
    if (request_irq(MVME147_IRQ_SCSI_DMA, mvme147_intr, 0, "MVME147 SCSI DMA", mvme147_intr))
	    goto err_free_irq;
#if 0	/* Disabled; causes problems booting */
    m147_pcc->scsi_interrupt = 0x10;	/* Assert SCSI bus reset */
    udelay(100);
    m147_pcc->scsi_interrupt = 0x00;	/* Negate SCSI bus reset */
    udelay(2000);
    m147_pcc->scsi_interrupt = 0x40;	/* Clear bus reset interrupt */
#endif
    m147_pcc->scsi_interrupt = 0x09;	/* Enable interrupt */

    m147_pcc->dma_cntrl = 0x00;		/* ensure DMA is stopped */
    m147_pcc->dma_intr = 0x89;		/* Ack and enable ints */

    return 1;

 err_free_irq:
    free_irq(MVME147_IRQ_SCSI_PORT, mvme147_intr);
 err_unregister:
    wd33c93_release();
    scsi_unregister(mvme147_host);
 err_out:
    return 0;
}