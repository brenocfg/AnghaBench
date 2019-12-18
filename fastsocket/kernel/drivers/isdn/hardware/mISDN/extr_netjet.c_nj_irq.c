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
typedef  int u8 ;
struct TYPE_4__ {int dmacur; int idx; int dmastart; scalar_t__ dmairq; } ;
struct TYPE_3__ {int dmacur; int idx; int dmastart; scalar_t__ dmairq; } ;
struct tiger_hw {int base; int last_is0; int /*<<< orphan*/  lock; TYPE_2__ send; TYPE_1__ recv; int /*<<< orphan*/  name; int /*<<< orphan*/  isac; int /*<<< orphan*/  irqcnt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int NJ_DMA_READ_ADR ; 
 int NJ_DMA_WRITE_ADR ; 
 int NJ_IRQM0_RD_MASK ; 
 int NJ_IRQM0_WR_MASK ; 
 int NJ_IRQSTAT0 ; 
 int NJ_IRQSTAT1 ; 
 int NJ_ISACIRQ ; 
 int ReadISAC_nj (struct tiger_hw*,int /*<<< orphan*/ ) ; 
 int inb (int) ; 
 void* inl (int) ; 
 int /*<<< orphan*/  mISDNisac_irq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  recv_tiger (struct tiger_hw*,int) ; 
 int /*<<< orphan*/  send_tiger (struct tiger_hw*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
nj_irq(int intno, void *dev_id)
{
	struct tiger_hw *card = dev_id;
	u8 val, s1val, s0val;

	spin_lock(&card->lock);
	s0val = inb(card->base | NJ_IRQSTAT0);
	s1val = inb(card->base | NJ_IRQSTAT1);
	if ((s1val & NJ_ISACIRQ) && (s0val == 0)) {
		/* shared IRQ */
		spin_unlock(&card->lock);
		return IRQ_NONE;
	}
	pr_debug("%s: IRQSTAT0 %02x IRQSTAT1 %02x\n", card->name, s0val, s1val);
	card->irqcnt++;
	if (!(s1val & NJ_ISACIRQ)) {
		val = ReadISAC_nj(card, ISAC_ISTA);
		if (val)
			mISDNisac_irq(&card->isac, val);
	}

	if (s0val)
		/* write to clear */
		outb(s0val, card->base | NJ_IRQSTAT0);
	else
		goto end;
	s1val = s0val;
	/* set bits in sval to indicate which page is free */
	card->recv.dmacur = inl(card->base | NJ_DMA_WRITE_ADR);
	card->recv.idx = (card->recv.dmacur - card->recv.dmastart) >> 2;
	if (card->recv.dmacur < card->recv.dmairq)
		s0val = 0x08;	/* the 2nd write area is free */
	else
		s0val = 0x04;	/* the 1st write area is free */

	card->send.dmacur = inl(card->base | NJ_DMA_READ_ADR);
	card->send.idx = (card->send.dmacur - card->send.dmastart) >> 2;
	if (card->send.dmacur < card->send.dmairq)
		s0val |= 0x02;	/* the 2nd read area is free */
	else
		s0val |= 0x01;	/* the 1st read area is free */

	pr_debug("%s: DMA Status %02x/%02x/%02x %d/%d\n", card->name,
		s1val, s0val, card->last_is0,
		card->recv.idx, card->send.idx);
	/* test if we have a DMA interrupt */
	if (s0val != card->last_is0) {
		if ((s0val & NJ_IRQM0_RD_MASK) !=
		    (card->last_is0 & NJ_IRQM0_RD_MASK))
			/* got a write dma int */
			send_tiger(card, s0val);
		if ((s0val & NJ_IRQM0_WR_MASK) !=
		    (card->last_is0 & NJ_IRQM0_WR_MASK))
			/* got a read dma int */
			recv_tiger(card, s0val);
	}
end:
	spin_unlock(&card->lock);
	return IRQ_HANDLED;
}