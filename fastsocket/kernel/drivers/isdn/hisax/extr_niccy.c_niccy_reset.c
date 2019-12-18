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
struct TYPE_3__ {scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ niccy; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ NICCY_PCI ; 
 scalar_t__ PCI_IRQ_CTRL_REG ; 
 int PCI_IRQ_ENABLE ; 
 int /*<<< orphan*/  inithscxisac (struct IsdnCardState*,int) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void niccy_reset(struct IsdnCardState *cs)
{
	if (cs->subtyp == NICCY_PCI) {
		int val;

		val = inl(cs->hw.niccy.cfg_reg + PCI_IRQ_CTRL_REG);
		val |= PCI_IRQ_ENABLE;
		outl(val, cs->hw.niccy.cfg_reg + PCI_IRQ_CTRL_REG);
	}
	inithscxisac(cs, 3);
}