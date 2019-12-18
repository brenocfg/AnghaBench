#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_7__ {int auxd; scalar_t__ base; } ;
struct TYPE_8__ {TYPE_3__ njet; } ;
struct TYPE_5__ {unsigned char lmr1; int /*<<< orphan*/  (* ph_command ) (struct IsdnCardState*,unsigned char,char*) ;} ;
struct TYPE_6__ {TYPE_1__ amd7930; } ;
struct IsdnCardState {int debug; TYPE_4__ hw; TYPE_2__ dc; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  Amd7930_init (struct IsdnCardState*) ; 
#define  CARD_INIT 135 
#define  CARD_RELEASE 134 
#define  CARD_RESET 133 
#define  CARD_TEST 132 
 int L1_DEB_ISAC ; 
#define  MDL_ASSIGN 131 
#define  MDL_BC_ASSIGN 130 
#define  MDL_BC_RELEASE 129 
#define  MDL_REMOVE 128 
 scalar_t__ NETJET_AUXDATA ; 
 int TJ_AMD_IRQ ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,unsigned char) ; 
 int /*<<< orphan*/  inittiger (struct IsdnCardState*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  release_io_netjet (struct IsdnCardState*) ; 
 int /*<<< orphan*/  reset_enpci (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,unsigned char,char*) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,unsigned char,char*) ; 

__attribute__((used)) static int
enpci_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;
        unsigned char *chan;

	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "enter:now PCI: card_msg: 0x%04X", mt);

        switch (mt) {
		case CARD_RESET:
			spin_lock_irqsave(&cs->lock, flags);
			reset_enpci(cs);
                        Amd7930_init(cs);
                        spin_unlock_irqrestore(&cs->lock, flags);
			break;
		case CARD_RELEASE:
			release_io_netjet(cs);
			break;
		case CARD_INIT:
			reset_enpci(cs);
			inittiger(cs);
			/* irq must be on here */
			Amd7930_init(cs);
			break;
		case CARD_TEST:
			break;
                case MDL_ASSIGN:
                        /* TEI assigned, LED1 on */
                        cs->hw.njet.auxd = TJ_AMD_IRQ << 1;
                        outb(cs->hw.njet.auxd, cs->hw.njet.base + NETJET_AUXDATA);
                        break;
                case MDL_REMOVE:
                        /* TEI removed, LEDs off */
	                cs->hw.njet.auxd = 0;
                        outb(0x00, cs->hw.njet.base + NETJET_AUXDATA);
                        break;
                case MDL_BC_ASSIGN:
                        /* activate B-channel */
                        chan = (unsigned char *)arg;

                        if (cs->debug & L1_DEB_ISAC)
		                debugl1(cs, "enter:now PCI: assign phys. BC %d in AMD LMR1", *chan);

                        cs->dc.amd7930.ph_command(cs, (cs->dc.amd7930.lmr1 | (*chan + 1)), "MDL_BC_ASSIGN");
                        /* at least one b-channel in use, LED 2 on */
                        cs->hw.njet.auxd |= TJ_AMD_IRQ << 2;
                        outb(cs->hw.njet.auxd, cs->hw.njet.base + NETJET_AUXDATA);
                        break;
                case MDL_BC_RELEASE:
                        /* deactivate B-channel */
                        chan = (unsigned char *)arg;

                        if (cs->debug & L1_DEB_ISAC)
		                debugl1(cs, "enter:now PCI: release phys. BC %d in Amd LMR1", *chan);

                        cs->dc.amd7930.ph_command(cs, (cs->dc.amd7930.lmr1 & ~(*chan + 1)), "MDL_BC_RELEASE");
                        /* no b-channel active -> LED2 off */
                        if (!(cs->dc.amd7930.lmr1 & 3)) {
                                cs->hw.njet.auxd &= ~(TJ_AMD_IRQ << 2);
                                outb(cs->hw.njet.auxd, cs->hw.njet.base + NETJET_AUXDATA);
                        }
                        break;
                default:
                        break;

	}
	return(0);
}