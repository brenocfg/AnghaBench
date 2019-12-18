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
struct TYPE_3__ {int ctrl_reg; int auxd; scalar_t__ auxa; scalar_t__ base; scalar_t__ dmactrl; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {int debug; TYPE_2__ hw; } ;

/* Variables and functions */
 int L1_DEB_ISAC ; 
 scalar_t__ NETJET_AUXCTRL ; 
 scalar_t__ NETJET_CTRL ; 
 scalar_t__ NETJET_IRQMASK1 ; 
 int TJ_AMD_IRQ ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void
reset_enpci(struct IsdnCardState *cs)
{
	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "enter:now PCI: reset");

	/* Reset on, (also for AMD) */
	cs->hw.njet.ctrl_reg = 0x07;
	outb(cs->hw.njet.ctrl_reg, cs->hw.njet.base + NETJET_CTRL);
	mdelay(20);
	/* Reset off */
	cs->hw.njet.ctrl_reg = 0x30;
	outb(cs->hw.njet.ctrl_reg, cs->hw.njet.base + NETJET_CTRL);
	/* 20ms delay */
	mdelay(20);
	cs->hw.njet.auxd = 0;  // LED-status
	cs->hw.njet.dmactrl = 0;
	outb(~TJ_AMD_IRQ, cs->hw.njet.base + NETJET_AUXCTRL);
	outb(TJ_AMD_IRQ, cs->hw.njet.base + NETJET_IRQMASK1);
	outb(cs->hw.njet.auxd, cs->hw.njet.auxa); // LED off
}