#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ expires; } ;
struct TYPE_6__ {int status; TYPE_3__ tl; int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/  ctrl; } ;
struct TYPE_7__ {TYPE_1__ diva; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 int DIVA_ASSIGN ; 
 scalar_t__ DIVA_IPACX_PCI ; 
 scalar_t__ DIVA_IPAC_ISA ; 
 scalar_t__ DIVA_IPAC_PCI ; 
 scalar_t__ DIVA_ISA ; 
 int /*<<< orphan*/  DIVA_ISA_LED_A ; 
 int /*<<< orphan*/  DIVA_ISA_LED_B ; 
 int /*<<< orphan*/  DIVA_PCI_LED_A ; 
 int /*<<< orphan*/  DIVA_PCI_LED_B ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  byteout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void
diva_led_handler(struct IsdnCardState *cs)
{
	int blink = 0;

	if ((cs->subtyp == DIVA_IPAC_ISA) ||
	    (cs->subtyp == DIVA_IPAC_PCI) ||
	    (cs->subtyp == DIVA_IPACX_PCI)   )
		return;
	del_timer(&cs->hw.diva.tl);
	if (cs->hw.diva.status & DIVA_ASSIGN)
		cs->hw.diva.ctrl_reg |= (DIVA_ISA == cs->subtyp) ?
			DIVA_ISA_LED_A : DIVA_PCI_LED_A;
	else {
		cs->hw.diva.ctrl_reg ^= (DIVA_ISA == cs->subtyp) ?
			DIVA_ISA_LED_A : DIVA_PCI_LED_A;
		blink = 250;
	}
	if (cs->hw.diva.status & 0xf000)
		cs->hw.diva.ctrl_reg |= (DIVA_ISA == cs->subtyp) ?
			DIVA_ISA_LED_B : DIVA_PCI_LED_B;
	else if (cs->hw.diva.status & 0x0f00) {
		cs->hw.diva.ctrl_reg ^= (DIVA_ISA == cs->subtyp) ?
			DIVA_ISA_LED_B : DIVA_PCI_LED_B;
		blink = 500;
	} else
		cs->hw.diva.ctrl_reg &= ~((DIVA_ISA == cs->subtyp) ?
			DIVA_ISA_LED_B : DIVA_PCI_LED_B);

	byteout(cs->hw.diva.ctrl, cs->hw.diva.ctrl_reg);
	if (blink) {
		init_timer(&cs->hw.diva.tl);
		cs->hw.diva.tl.expires = jiffies + ((blink * HZ) / 1000);
		add_timer(&cs->hw.diva.tl);
	}
}