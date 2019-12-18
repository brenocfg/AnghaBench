#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct IsdnCardState {int /*<<< orphan*/  lock; int /*<<< orphan*/  debug; } ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  L1_DEB_IPAC ; 
 int /*<<< orphan*/  enable_bkm_int (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  inithscxisac (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  release_io_sct_quadro (struct IsdnCardState*) ; 
 int /*<<< orphan*/  reset_bkm (struct IsdnCardState*) ; 
 int /*<<< orphan*/  set_ipac_active (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
BKM_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			/* Disable ints */
			set_ipac_active(cs, 0);
			enable_bkm_int(cs, 0);
			reset_bkm(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			return (0);
		case CARD_RELEASE:
			/* Sanity */
			spin_lock_irqsave(&cs->lock, flags);
			set_ipac_active(cs, 0);
			enable_bkm_int(cs, 0);
			spin_unlock_irqrestore(&cs->lock, flags);
			release_io_sct_quadro(cs);
			return (0);
		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			cs->debug |= L1_DEB_IPAC;
			set_ipac_active(cs, 1);
			inithscxisac(cs, 3);
			/* Enable ints */
			enable_bkm_int(cs, 1);
			spin_unlock_irqrestore(&cs->lock, flags);
			return (0);
		case CARD_TEST:
			return (0);
	}
	return (0);
}