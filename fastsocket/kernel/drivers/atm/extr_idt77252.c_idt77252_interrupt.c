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
typedef  int u32 ;
struct idt77252_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  tqueue; int /*<<< orphan*/ * irqstat; int /*<<< orphan*/  name; TYPE_2__* atmdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* interrupt ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IDT77252_BIT_INTERRUPT ; 
 int /*<<< orphan*/  INTPRINTK (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SAR_CFG_FBIE ; 
 int /*<<< orphan*/  SAR_REG_CFG ; 
 int /*<<< orphan*/  SAR_REG_STAT ; 
 int SAR_STAT_EPDU ; 
 int SAR_STAT_FBQ0A ; 
 int SAR_STAT_FBQ1A ; 
 int SAR_STAT_FBQ2A ; 
 int SAR_STAT_FBQ3A ; 
 int SAR_STAT_PHYI ; 
 int SAR_STAT_RAWCF ; 
 int SAR_STAT_RSQAF ; 
 int SAR_STAT_RSQF ; 
 int SAR_STAT_TMROF ; 
 int SAR_STAT_TSIF ; 
 int SAR_STAT_TSQF ; 
 int SAR_STAT_TXICP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idt77252_collect_stat (struct idt77252_dev*) ; 
 int /*<<< orphan*/  idt77252_rx (struct idt77252_dev*) ; 
 int /*<<< orphan*/  idt77252_rx_raw (struct idt77252_dev*) ; 
 int /*<<< orphan*/  idt77252_tx (struct idt77252_dev*) ; 
 int /*<<< orphan*/  idt77252_tx_dump (struct idt77252_dev*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
idt77252_interrupt(int irq, void *dev_id)
{
	struct idt77252_dev *card = dev_id;
	u32 stat;

	stat = readl(SAR_REG_STAT) & 0xffff;
	if (!stat)	/* no interrupt for us */
		return IRQ_NONE;

	if (test_and_set_bit(IDT77252_BIT_INTERRUPT, &card->flags)) {
		printk("%s: Re-entering irq_handler()\n", card->name);
		goto out;
	}

	writel(stat, SAR_REG_STAT);	/* reset interrupt */

	if (stat & SAR_STAT_TSIF) {	/* entry written to TSQ  */
		INTPRINTK("%s: TSIF\n", card->name);
		card->irqstat[15]++;
		idt77252_tx(card);
	}
	if (stat & SAR_STAT_TXICP) {	/* Incomplete CS-PDU has  */
		INTPRINTK("%s: TXICP\n", card->name);
		card->irqstat[14]++;
#ifdef CONFIG_ATM_IDT77252_DEBUG
		idt77252_tx_dump(card);
#endif
	}
	if (stat & SAR_STAT_TSQF) {	/* TSQ 7/8 full           */
		INTPRINTK("%s: TSQF\n", card->name);
		card->irqstat[12]++;
		idt77252_tx(card);
	}
	if (stat & SAR_STAT_TMROF) {	/* Timer overflow         */
		INTPRINTK("%s: TMROF\n", card->name);
		card->irqstat[11]++;
		idt77252_collect_stat(card);
	}

	if (stat & SAR_STAT_EPDU) {	/* Got complete CS-PDU    */
		INTPRINTK("%s: EPDU\n", card->name);
		card->irqstat[5]++;
		idt77252_rx(card);
	}
	if (stat & SAR_STAT_RSQAF) {	/* RSQ is 7/8 full        */
		INTPRINTK("%s: RSQAF\n", card->name);
		card->irqstat[1]++;
		idt77252_rx(card);
	}
	if (stat & SAR_STAT_RSQF) {	/* RSQ is full            */
		INTPRINTK("%s: RSQF\n", card->name);
		card->irqstat[6]++;
		idt77252_rx(card);
	}
	if (stat & SAR_STAT_RAWCF) {	/* Raw cell received      */
		INTPRINTK("%s: RAWCF\n", card->name);
		card->irqstat[4]++;
		idt77252_rx_raw(card);
	}

	if (stat & SAR_STAT_PHYI) {	/* PHY device interrupt   */
		INTPRINTK("%s: PHYI", card->name);
		card->irqstat[10]++;
		if (card->atmdev->phy && card->atmdev->phy->interrupt)
			card->atmdev->phy->interrupt(card->atmdev);
	}

	if (stat & (SAR_STAT_FBQ0A | SAR_STAT_FBQ1A |
		    SAR_STAT_FBQ2A | SAR_STAT_FBQ3A)) {

		writel(readl(SAR_REG_CFG) & ~(SAR_CFG_FBIE), SAR_REG_CFG);

		INTPRINTK("%s: FBQA: %04x\n", card->name, stat);

		if (stat & SAR_STAT_FBQ0A)
			card->irqstat[2]++;
		if (stat & SAR_STAT_FBQ1A)
			card->irqstat[3]++;
		if (stat & SAR_STAT_FBQ2A)
			card->irqstat[7]++;
		if (stat & SAR_STAT_FBQ3A)
			card->irqstat[8]++;

		schedule_work(&card->tqueue);
	}

out:
	clear_bit(IDT77252_BIT_INTERRUPT, &card->flags);
	return IRQ_HANDLED;
}