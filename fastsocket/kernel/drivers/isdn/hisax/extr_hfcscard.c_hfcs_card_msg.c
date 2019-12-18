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
struct TYPE_3__ {int /*<<< orphan*/  mst_m; int /*<<< orphan*/  ctmt; int /*<<< orphan*/  timer; } ;
struct TYPE_4__ {TYPE_1__ hfcD; } ;
struct IsdnCardState {int debug; int /*<<< orphan*/  lock; TYPE_2__ hw; int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  HFCD_CTMT ; 
 int /*<<< orphan*/  HFCD_DATA ; 
 int /*<<< orphan*/  HFCD_MST_MODE ; 
 int /*<<< orphan*/  HFCD_TIM800 ; 
 int HZ ; 
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int) ; 
 int /*<<< orphan*/  init2bds0 (struct IsdnCardState*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_io_hfcs (struct IsdnCardState*) ; 
 int /*<<< orphan*/  reset_hfcs (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hfcs_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;
	int delay;

	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "HFCS: card_msg %x", mt);
	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			reset_hfcs(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_RELEASE:
			release_io_hfcs(cs);
			return(0);
		case CARD_INIT:
			delay = (75*HZ)/100 +1;
			mod_timer(&cs->hw.hfcD.timer, jiffies + delay);
			spin_lock_irqsave(&cs->lock, flags);
			reset_hfcs(cs);
			init2bds0(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			delay = (80*HZ)/1000 +1;
			msleep(80);
			spin_lock_irqsave(&cs->lock, flags);
			cs->hw.hfcD.ctmt |= HFCD_TIM800;
			cs->BC_Write_Reg(cs, HFCD_DATA, HFCD_CTMT, cs->hw.hfcD.ctmt); 
			cs->BC_Write_Reg(cs, HFCD_DATA, HFCD_MST_MODE, cs->hw.hfcD.mst_m);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_TEST:
			return(0);
	}
	return(0);
}