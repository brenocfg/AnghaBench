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
struct TYPE_3__ {scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ NETJET_IRQMASK1 ; 
 int TJ_AMD_IRQ ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void
enpci_setIrqMask(struct IsdnCardState *cs, unsigned char val) {
        if (!val)
	        outb(0x00, cs->hw.njet.base+NETJET_IRQMASK1);
        else
	        outb(TJ_AMD_IRQ, cs->hw.njet.base+NETJET_IRQMASK1);
}