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
struct TYPE_3__ {int /*<<< orphan*/  cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ avm; } ;
struct IsdnCardState {int /*<<< orphan*/  lock; TYPE_2__ hw; } ;

/* Variables and functions */
 int AVM_STATUS0_DIS_TIMER ; 
 int AVM_STATUS0_ENA_IRQ ; 
 int AVM_STATUS0_RES_TIMER ; 
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  WriteISAC (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_pending_isac_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  inithdlc (struct IsdnCardState*) ; 
 int /*<<< orphan*/  initisac (struct IsdnCardState*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_avmpcipnp (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
AVM_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			reset_avmpcipnp(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_RELEASE:
			outb(0, cs->hw.avm.cfg_reg + 2);
			release_region(cs->hw.avm.cfg_reg, 32);
			return(0);
		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			reset_avmpcipnp(cs);
			clear_pending_isac_ints(cs);
			initisac(cs);
			inithdlc(cs);
			outb(AVM_STATUS0_DIS_TIMER | AVM_STATUS0_RES_TIMER,
				cs->hw.avm.cfg_reg + 2);
			WriteISAC(cs, ISAC_MASK, 0);
			outb(AVM_STATUS0_DIS_TIMER | AVM_STATUS0_RES_TIMER |
				AVM_STATUS0_ENA_IRQ, cs->hw.avm.cfg_reg + 2);
			/* RESET Receiver and Transmitter */
			WriteISAC(cs, ISAC_CMDR, 0x41);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_TEST:
			return(0);
	}
	return(0);
}