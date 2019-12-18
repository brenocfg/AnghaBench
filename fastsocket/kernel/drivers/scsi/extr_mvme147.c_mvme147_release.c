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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVME147_IRQ_SCSI_DMA ; 
 int /*<<< orphan*/  MVME147_IRQ_SCSI_PORT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvme147_intr ; 
 int /*<<< orphan*/  wd33c93_release () ; 

int mvme147_release(struct Scsi_Host *instance)
{
#ifdef MODULE
    /* XXX Make sure DMA is stopped! */
    wd33c93_release();
    free_irq(MVME147_IRQ_SCSI_PORT, mvme147_intr);
    free_irq(MVME147_IRQ_SCSI_DMA, mvme147_intr);
#endif
    return 1;
}