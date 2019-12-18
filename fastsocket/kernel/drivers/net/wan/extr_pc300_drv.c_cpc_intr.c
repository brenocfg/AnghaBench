#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int type; scalar_t__ intctl_reg; scalar_t__ plxbase; int /*<<< orphan*/  rambase; } ;
struct TYPE_6__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ pc300_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  PC300_RSV 130 
#define  PC300_TE 129 
#define  PC300_X21 128 
 int volatile PLX_9050_LINT1_STATUS ; 
 int volatile PLX_9050_LINT2_STATUS ; 
 int volatile cpc_readb (scalar_t__) ; 
 int /*<<< orphan*/  falc_intr (TYPE_2__*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  sca_intr (TYPE_2__*) ; 

__attribute__((used)) static irqreturn_t cpc_intr(int irq, void *dev_id)
{
	pc300_t *card = dev_id;
	volatile u8 plx_status;

	if (!card) {
#ifdef PC300_DEBUG_INTR
		printk("cpc_intr: spurious intr %d\n", irq);
#endif
		return IRQ_NONE;		/* spurious intr */
	}

	if (!card->hw.rambase) {
#ifdef PC300_DEBUG_INTR
		printk("cpc_intr: spurious intr2 %d\n", irq);
#endif
		return IRQ_NONE;		/* spurious intr */
	}

	switch (card->hw.type) {
		case PC300_RSV:
		case PC300_X21:
			sca_intr(card);
			break;

		case PC300_TE:
			while ( (plx_status = (cpc_readb(card->hw.plxbase + card->hw.intctl_reg) &
				 (PLX_9050_LINT1_STATUS | PLX_9050_LINT2_STATUS))) != 0) {
				if (plx_status & PLX_9050_LINT1_STATUS) {	/* SCA Interrupt */
					sca_intr(card);
				}
				if (plx_status & PLX_9050_LINT2_STATUS) {	/* FALC Interrupt */
					falc_intr(card);
				}
			}
			break;
	}
	return IRQ_HANDLED;
}