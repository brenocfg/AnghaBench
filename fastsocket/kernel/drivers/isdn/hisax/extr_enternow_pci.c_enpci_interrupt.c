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
struct TYPE_3__ {unsigned char last_is0; unsigned char irqstat0; scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {int /*<<< orphan*/  lock; int /*<<< orphan*/  HW_Flags; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  Amd7930_interrupt (struct IsdnCardState*,unsigned char) ; 
 int /*<<< orphan*/  FLG_LOCK_ATOMIC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ NETJET_DMA_READ_ADR ; 
 scalar_t__ NETJET_DMA_READ_IRQ ; 
 scalar_t__ NETJET_DMA_WRITE_ADR ; 
 scalar_t__ NETJET_DMA_WRITE_IRQ ; 
 int NETJET_IRQM0_READ ; 
 int NETJET_IRQM0_WRITE ; 
 scalar_t__ NETJET_IRQSTAT0 ; 
 scalar_t__ NETJET_IRQSTAT1 ; 
 unsigned char ReadByteAmd7930 (struct IsdnCardState*,int) ; 
 unsigned char TJ_AMD_IRQ ; 
 unsigned char inb (scalar_t__) ; 
 scalar_t__ inl (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  read_tiger (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_tiger (struct IsdnCardState*) ; 

__attribute__((used)) static irqreturn_t
enpci_interrupt(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	unsigned char s0val, s1val, ir;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	s1val = inb(cs->hw.njet.base + NETJET_IRQSTAT1);

        /* AMD threw an interrupt */
	if (!(s1val & TJ_AMD_IRQ)) {
                /* read and clear interrupt-register */
		ir = ReadByteAmd7930(cs, 0x00);
		Amd7930_interrupt(cs, ir);
		s1val = 1;
	} else
		s1val = 0;
	s0val = inb(cs->hw.njet.base + NETJET_IRQSTAT0);
	if ((s0val | s1val)==0) { // shared IRQ
		spin_unlock_irqrestore(&cs->lock, flags);
		return IRQ_NONE;
	} 
	if (s0val)
		outb(s0val, cs->hw.njet.base + NETJET_IRQSTAT0);

	/* DMA-Interrupt: B-channel-stuff */
	/* set bits in sval to indicate which page is free */
	if (inl(cs->hw.njet.base + NETJET_DMA_WRITE_ADR) <
		inl(cs->hw.njet.base + NETJET_DMA_WRITE_IRQ))
		/* the 2nd write page is free */
		s0val = 0x08;
	else	/* the 1st write page is free */
		s0val = 0x04;
	if (inl(cs->hw.njet.base + NETJET_DMA_READ_ADR) <
		inl(cs->hw.njet.base + NETJET_DMA_READ_IRQ))
		/* the 2nd read page is free */
		s0val = s0val | 0x02;
	else	/* the 1st read page is free */
		s0val = s0val | 0x01;
	if (s0val != cs->hw.njet.last_is0) /* we have a DMA interrupt */
	{
		if (test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
			spin_unlock_irqrestore(&cs->lock, flags);
			return IRQ_HANDLED;
		}
		cs->hw.njet.irqstat0 = s0val;
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_READ) !=
			(cs->hw.njet.last_is0 & NETJET_IRQM0_READ))
			/* we have a read dma int */
			read_tiger(cs);
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_WRITE) !=
			(cs->hw.njet.last_is0 & NETJET_IRQM0_WRITE))
			/* we have a write dma int */
			write_tiger(cs);
		test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}