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
struct IsdnCardState {int /*<<< orphan*/  lock; TYPE_3__* bcs; int /*<<< orphan*/  subtyp; } ;
struct TYPE_4__ {int tsaxr0; int tsaxr1; } ;
struct TYPE_5__ {TYPE_1__ hscx; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  MAX_WAITING_CALLS ; 
 int /*<<< orphan*/  R647 ; 
 int /*<<< orphan*/  R685 ; 
 int /*<<< orphan*/  inithscxisac (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  release_io_gazel (struct IsdnCardState*) ; 
 int /*<<< orphan*/  reset_gazel (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Gazel_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			reset_gazel(cs);
			spin_unlock_irqrestore(&cs->lock, flags);
			return (0);
		case CARD_RELEASE:
			release_io_gazel(cs);
			return (0);
		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			inithscxisac(cs, 1);
			if ((cs->subtyp==R647)||(cs->subtyp==R685)) {
				int i;
				for (i=0;i<(2+MAX_WAITING_CALLS);i++) {
					cs->bcs[i].hw.hscx.tsaxr0 = 0x1f;
					cs->bcs[i].hw.hscx.tsaxr1 = 0x23;
				}
			}
			spin_unlock_irqrestore(&cs->lock, flags);
			return (0);
		case CARD_TEST:
			return (0);
	}
	return (0);
}