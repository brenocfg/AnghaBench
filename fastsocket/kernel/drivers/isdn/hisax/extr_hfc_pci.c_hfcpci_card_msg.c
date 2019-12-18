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
struct TYPE_3__ {int /*<<< orphan*/  mst_m; int /*<<< orphan*/  int_m1; } ;
struct TYPE_4__ {TYPE_1__ hfcpci; } ;
struct IsdnCardState {int debug; int /*<<< orphan*/  lock; TYPE_2__ hw; } ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  HFCPCI_INTS_TIMER ; 
 int /*<<< orphan*/  HFCPCI_INT_M1 ; 
 int /*<<< orphan*/  HFCPCI_MST_MODE ; 
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  Write_hfc (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int) ; 
 int /*<<< orphan*/  inithfcpci (struct IsdnCardState*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_io_hfcpci (struct IsdnCardState*) ; 
 int /*<<< orphan*/  reset_hfcpci (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hfcpci_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "HFCPCI: card_msg %x", mt);
	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			reset_hfcpci(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			return (0);
		case CARD_RELEASE:
			release_io_hfcpci(cs);
			return (0);
		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			inithfcpci(cs);
			reset_hfcpci(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			msleep(80);				/* Timeout 80ms */
			/* now switch timer interrupt off */
			spin_lock_irqsave(&cs->lock, flags);
			cs->hw.hfcpci.int_m1 &= ~HFCPCI_INTS_TIMER;
			Write_hfc(cs, HFCPCI_INT_M1, cs->hw.hfcpci.int_m1);
			/* reinit mode reg */
			Write_hfc(cs, HFCPCI_MST_MODE, cs->hw.hfcpci.mst_m);
			spin_unlock_irqrestore(&cs->lock, flags);
			return (0);
		case CARD_TEST:
			return (0);
	}
	return (0);
}