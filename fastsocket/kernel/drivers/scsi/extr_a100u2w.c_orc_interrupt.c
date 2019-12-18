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
typedef  int u8 ;
struct orc_scb {int status; } ;
struct orc_host {scalar_t__ scb_virt; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ ORC_RQUEUE ; 
 scalar_t__ ORC_RQUEUECNT ; 
 scalar_t__ inb (scalar_t__) ; 
 int /*<<< orphan*/  inia100_scb_handler (struct orc_host*,struct orc_scb*) ; 

__attribute__((used)) static irqreturn_t orc_interrupt(struct orc_host * host)
{
	u8 scb_index;
	struct orc_scb *scb;

	/* Check if we have an SCB queued for servicing */
	if (inb(host->base + ORC_RQUEUECNT) == 0)
		return IRQ_NONE;

	do {
		/* Get the SCB index of the SCB to service */
		scb_index = inb(host->base + ORC_RQUEUE);

		/* Translate it back to a host pointer */
		scb = (struct orc_scb *) ((unsigned long) host->scb_virt + (unsigned long) (sizeof(struct orc_scb) * scb_index));
		scb->status = 0x0;
		/* Process the SCB */
		inia100_scb_handler(host, scb);
	} while (inb(host->base + ORC_RQUEUECNT));
	return IRQ_HANDLED;
}