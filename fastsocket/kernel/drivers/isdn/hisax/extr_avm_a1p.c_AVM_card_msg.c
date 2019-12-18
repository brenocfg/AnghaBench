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
struct TYPE_3__ {scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ avm; } ;
struct IsdnCardState {int /*<<< orphan*/  lock; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ ASL0_OFFSET ; 
 int ASL0_W_IRQENABLE ; 
 int ASL0_W_RESET ; 
 int ASL0_W_TDISABLE ; 
 int ASL0_W_TRESET ; 
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int HZ ; 
 int /*<<< orphan*/  HZDELAY (int) ; 
 int /*<<< orphan*/  byteout (scalar_t__,int) ; 
 int /*<<< orphan*/  clear_pending_hscx_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  clear_pending_isac_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  inithscxisac (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
AVM_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			byteout(cs->hw.avm.cfg_reg+ASL0_OFFSET,0x00);
			HZDELAY(HZ / 5 + 1);
			byteout(cs->hw.avm.cfg_reg+ASL0_OFFSET,ASL0_W_RESET);
			HZDELAY(HZ / 5 + 1);
			byteout(cs->hw.avm.cfg_reg+ASL0_OFFSET,0x00);
			spin_unlock_irqrestore(&cs->lock, flags);
			return 0;

		case CARD_RELEASE:
			/* free_irq is done in HiSax_closecard(). */
		        /* free_irq(cs->irq, cs); */
			return 0;

		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			byteout(cs->hw.avm.cfg_reg+ASL0_OFFSET,ASL0_W_TDISABLE|ASL0_W_TRESET|ASL0_W_IRQENABLE);
			clear_pending_isac_ints(cs);
			clear_pending_hscx_ints(cs);
			inithscxisac(cs, 1);
			inithscxisac(cs, 2);
			spin_unlock_irqrestore(&cs->lock, flags);
			return 0;

		case CARD_TEST:
			/* we really don't need it for the PCMCIA Version */
			return 0;

		default:
			/* all card drivers ignore others, so we do the same */
			return 0;
	}
	return 0;
}