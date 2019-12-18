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
typedef  int u_char ;
struct TYPE_8__ {scalar_t__ expires; } ;
struct TYPE_6__ {int status; int ctrl_reg; TYPE_3__ tl; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  isac; int /*<<< orphan*/  ale; } ;
struct TYPE_7__ {TYPE_1__ elsa; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 int ELSA_ASSIGN ; 
 int ELSA_BAD_PWR ; 
 int ELSA_IPAC_LINE_LED ; 
 int ELSA_IPAC_STAT_LED ; 
 int ELSA_LINE_LED ; 
 scalar_t__ ELSA_PCMCIA ; 
 scalar_t__ ELSA_PCMCIA_IPAC ; 
 scalar_t__ ELSA_QS1000PCI ; 
 scalar_t__ ELSA_QS3000PCI ; 
 int ELSA_STAT_LED ; 
 int HZ ; 
 int /*<<< orphan*/  IPAC_ATX ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  byteout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
elsa_led_handler(struct IsdnCardState *cs)
{
	int blink = 0;

	if (cs->subtyp == ELSA_PCMCIA || cs->subtyp == ELSA_PCMCIA_IPAC)
		return;
	del_timer(&cs->hw.elsa.tl);
	if (cs->hw.elsa.status & ELSA_ASSIGN)
		cs->hw.elsa.ctrl_reg |= ELSA_STAT_LED;
	else if (cs->hw.elsa.status & ELSA_BAD_PWR)
		cs->hw.elsa.ctrl_reg &= ~ELSA_STAT_LED;
	else {
		cs->hw.elsa.ctrl_reg ^= ELSA_STAT_LED;
		blink = 250;
	}
	if (cs->hw.elsa.status & 0xf000)
		cs->hw.elsa.ctrl_reg |= ELSA_LINE_LED;
	else if (cs->hw.elsa.status & 0x0f00) {
		cs->hw.elsa.ctrl_reg ^= ELSA_LINE_LED;
		blink = 500;
	} else
		cs->hw.elsa.ctrl_reg &= ~ELSA_LINE_LED;

	if ((cs->subtyp == ELSA_QS1000PCI) ||
		(cs->subtyp == ELSA_QS3000PCI)) {
		u_char led = 0xff;
		if (cs->hw.elsa.ctrl_reg & ELSA_LINE_LED)
			led ^= ELSA_IPAC_LINE_LED;
		if (cs->hw.elsa.ctrl_reg & ELSA_STAT_LED)
			led ^= ELSA_IPAC_STAT_LED;
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_ATX, led);
	} else
		byteout(cs->hw.elsa.ctrl, cs->hw.elsa.ctrl_reg);
	if (blink) {
		init_timer(&cs->hw.elsa.tl);
		cs->hw.elsa.tl.expires = jiffies + ((blink * HZ) / 1000);
		add_timer(&cs->hw.elsa.tl);
	}
}