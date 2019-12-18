#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int n_ports; int /*<<< orphan*/ * ports; scalar_t__ plx; } ;
typedef  TYPE_1__ card_t ;

/* Variables and functions */
 int DOORBELL_FROM_CARD_CABLE_0 ; 
 int DOORBELL_FROM_CARD_RX ; 
 int DOORBELL_FROM_CARD_TX_0 ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ PLX_DOORBELL_FROM_CARD ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wanxl_cable_intr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wanxl_rx_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  wanxl_tx_intr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t wanxl_intr(int irq, void* dev_id)
{
        card_t *card = dev_id;
        int i;
        u32 stat;
        int handled = 0;


        while((stat = readl(card->plx + PLX_DOORBELL_FROM_CARD)) != 0) {
                handled = 1;
		writel(stat, card->plx + PLX_DOORBELL_FROM_CARD);

                for (i = 0; i < card->n_ports; i++) {
			if (stat & (1 << (DOORBELL_FROM_CARD_TX_0 + i)))
				wanxl_tx_intr(&card->ports[i]);
			if (stat & (1 << (DOORBELL_FROM_CARD_CABLE_0 + i)))
				wanxl_cable_intr(&card->ports[i]);
		}
		if (stat & (1 << DOORBELL_FROM_CARD_RX))
			wanxl_rx_intr(card);
        }

        return IRQ_RETVAL(handled);
}