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
struct TYPE_3__ {scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ avm; } ;
struct IsdnCardState {int /*<<< orphan*/  lock; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AVM_STATUS0_IRQ_HDLC ; 
 int AVM_STATUS0_IRQ_ISAC ; 
 int AVM_STATUS0_IRQ_MASK ; 
 int /*<<< orphan*/  HDLC_irq_main (struct IsdnCardState*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int ReadISAC (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteISAC (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  isac_interrupt (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
avm_pcipnp_interrupt(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_long flags;
	u_char val;
	u_char sval;

	spin_lock_irqsave(&cs->lock, flags);
	sval = inb(cs->hw.avm.cfg_reg + 2);
	if ((sval & AVM_STATUS0_IRQ_MASK) == AVM_STATUS0_IRQ_MASK) {
		/* possible a shared  IRQ reqest */
		spin_unlock_irqrestore(&cs->lock, flags);
		return IRQ_NONE;
	}
	if (!(sval & AVM_STATUS0_IRQ_ISAC)) {
		val = ReadISAC(cs, ISAC_ISTA);
		isac_interrupt(cs, val);
	}
	if (!(sval & AVM_STATUS0_IRQ_HDLC)) {
		HDLC_irq_main(cs);
	}
	WriteISAC(cs, ISAC_MASK, 0xFF);
	WriteISAC(cs, ISAC_MASK, 0x0);
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}