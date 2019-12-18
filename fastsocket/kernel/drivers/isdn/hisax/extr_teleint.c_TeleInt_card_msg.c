#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_6__ {int /*<<< orphan*/  expires; } ;
struct TYPE_4__ {TYPE_3__ timer; } ;
struct TYPE_5__ {TYPE_1__ hfc; } ;
struct IsdnCardState {TYPE_2__ hw; int /*<<< orphan*/  lock; int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int HZ ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  clear_pending_isac_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  inithfc (struct IsdnCardState*) ; 
 int /*<<< orphan*/  initisac (struct IsdnCardState*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  release_io_TeleInt (struct IsdnCardState*) ; 
 int /*<<< orphan*/  reset_TeleInt (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
TeleInt_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;
	int delay;

	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			reset_TeleInt(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_RELEASE:
			release_io_TeleInt(cs);
			return(0);
		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			reset_TeleInt(cs);
			inithfc(cs);
			clear_pending_isac_ints(cs);
			initisac(cs);
			/* Reenable all IRQ */
			cs->writeisac(cs, ISAC_MASK, 0);
			cs->writeisac(cs, ISAC_CMDR, 0x41);
			spin_unlock_irqrestore(&cs->lock, flags);
			delay = HZ/100;
			if (!delay)
				delay = 1;
			cs->hw.hfc.timer.expires = jiffies + delay;
			add_timer(&cs->hw.hfc.timer);
			return(0);
		case CARD_TEST:
			return(0);
	}
	return(0);
}