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
struct TYPE_3__ {scalar_t__ isar; } ;
struct TYPE_4__ {TYPE_1__ isurf; } ;
struct IsdnCardState {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;TYPE_2__ hw; } ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 scalar_t__ ISAR_IRQBIT ; 
 int /*<<< orphan*/  ISURF_RESET ; 
 int /*<<< orphan*/  clear_pending_isac_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  initisac (struct IsdnCardState*) ; 
 int /*<<< orphan*/  initisar (struct IsdnCardState*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  release_io_isurf (struct IsdnCardState*) ; 
 int /*<<< orphan*/  reset_isurf (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ISurf_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			reset_isurf(cs, ISURF_RESET);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_RELEASE:
			release_io_isurf(cs);
			return(0);
		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			reset_isurf(cs, ISURF_RESET);
			clear_pending_isac_ints(cs);
			writeb(0, cs->hw.isurf.isar+ISAR_IRQBIT);mb();
			initisac(cs);
			initisar(cs);
			/* Reenable ISAC IRQ */
			cs->writeisac(cs, ISAC_MASK, 0);
			/* RESET Receiver and Transmitter */
			cs->writeisac(cs, ISAC_CMDR, 0x41);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_TEST:
			return(0);
	}
	return(0);
}