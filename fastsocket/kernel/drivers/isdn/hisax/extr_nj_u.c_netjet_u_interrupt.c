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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_char ;
struct TYPE_3__ {int last_is0; int irqstat0; scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {int debug; int /*<<< orphan*/  lock; int /*<<< orphan*/  HW_Flags; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_LOCK_ATOMIC ; 
 int /*<<< orphan*/  ICC_ISTA ; 
 int /*<<< orphan*/  ICC_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int L1_DEB_ISAC ; 
 scalar_t__ NETJET_DMA_READ_ADR ; 
 scalar_t__ NETJET_DMA_READ_IRQ ; 
 scalar_t__ NETJET_DMA_WRITE_ADR ; 
 scalar_t__ NETJET_DMA_WRITE_IRQ ; 
 int NETJET_IRQM0_READ ; 
 int NETJET_IRQM0_WRITE ; 
 scalar_t__ NETJET_IRQSTAT1 ; 
 int NETJET_ISACIRQ ; 
 int NETjet_ReadIC (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETjet_WriteIC (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int bytein (scalar_t__) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int,int) ; 
 int /*<<< orphan*/  icc_interrupt (struct IsdnCardState*,int) ; 
 scalar_t__ inl (scalar_t__) ; 
 int /*<<< orphan*/  read_tiger (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_tiger (struct IsdnCardState*) ; 

__attribute__((used)) static irqreturn_t
netjet_u_interrupt(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_char val, sval;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	if (!((sval = bytein(cs->hw.njet.base + NETJET_IRQSTAT1)) &
		NETJET_ISACIRQ)) {
		val = NETjet_ReadIC(cs, ICC_ISTA);
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "tiger: i1 %x %x", sval, val);
		if (val) {
			icc_interrupt(cs, val);
			NETjet_WriteIC(cs, ICC_MASK, 0xFF);
			NETjet_WriteIC(cs, ICC_MASK, 0x0);
		}
	}
	/* start new code 13/07/00 GE */
	/* set bits in sval to indicate which page is free */
	if (inl(cs->hw.njet.base + NETJET_DMA_WRITE_ADR) <
		inl(cs->hw.njet.base + NETJET_DMA_WRITE_IRQ))
		/* the 2nd write page is free */
		sval = 0x08;
	else	/* the 1st write page is free */
		sval = 0x04;	
	if (inl(cs->hw.njet.base + NETJET_DMA_READ_ADR) <
		inl(cs->hw.njet.base + NETJET_DMA_READ_IRQ))
		/* the 2nd read page is free */
		sval = sval | 0x02;
	else	/* the 1st read page is free */
		sval = sval | 0x01;	
	if (sval != cs->hw.njet.last_is0) /* we have a DMA interrupt */
	{
		if (test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
			spin_unlock_irqrestore(&cs->lock, flags);
			return IRQ_HANDLED;
		}
		cs->hw.njet.irqstat0 = sval;
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_READ) != 
			(cs->hw.njet.last_is0 & NETJET_IRQM0_READ))
			/* we have a read dma int */
			read_tiger(cs);
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_WRITE) !=
			(cs->hw.njet.last_is0 & NETJET_IRQM0_WRITE))
			/* we have a write dma int */
			write_tiger(cs);
		/* end new code 13/07/00 GE */
		test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}