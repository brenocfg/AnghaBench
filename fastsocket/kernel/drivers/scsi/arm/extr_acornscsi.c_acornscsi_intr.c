#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  scalar_t__ intr_ret_t ;
struct TYPE_7__ {scalar_t__ xfer_required; } ;
struct TYPE_8__ {TYPE_1__ dma; scalar_t__ fast; } ;
typedef  TYPE_2__ AS_Host ;

/* Variables and functions */
 scalar_t__ INTR_IDLE ; 
 scalar_t__ INTR_NEXT_COMMAND ; 
 scalar_t__ INT_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  acornscsi_dma_intr (TYPE_2__*) ; 
 int /*<<< orphan*/  acornscsi_dma_xfer (TYPE_2__*) ; 
 scalar_t__ acornscsi_kick (TYPE_2__*) ; 
 scalar_t__ acornscsi_sbicintr (TYPE_2__*,int) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static irqreturn_t
acornscsi_intr(int irq, void *dev_id)
{
    AS_Host *host = (AS_Host *)dev_id;
    intr_ret_t ret;
    int iostatus;
    int in_irq = 0;

    do {
	ret = INTR_IDLE;

	iostatus = readb(host->fast + INT_REG);

	if (iostatus & 2) {
	    acornscsi_dma_intr(host);
	    iostatus = readb(host->fast + INT_REG);
	}

	if (iostatus & 8)
	    ret = acornscsi_sbicintr(host, in_irq);

	/*
	 * If we have a transfer pending, start it.
	 * Only start it if the interface has already started transferring
	 * it's data
	 */
	if (host->dma.xfer_required)
	    acornscsi_dma_xfer(host);

	if (ret == INTR_NEXT_COMMAND)
	    ret = acornscsi_kick(host);

	in_irq = 1;
    } while (ret != INTR_IDLE);

    return IRQ_HANDLED;
}