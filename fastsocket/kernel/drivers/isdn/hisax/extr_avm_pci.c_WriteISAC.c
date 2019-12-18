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
typedef  int u_char ;
struct TYPE_3__ {scalar_t__ isac; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ avm; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int AVM_ISAC_REG_HIGH ; 
 int AVM_ISAC_REG_LOW ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void
WriteISAC(struct IsdnCardState *cs, u_char offset, u_char value)
{
	register u_char idx = (offset > 0x2f) ? AVM_ISAC_REG_HIGH : AVM_ISAC_REG_LOW;

	outb(idx, cs->hw.avm.cfg_reg + 4);
	outb(value, cs->hw.avm.isac + (offset & 0xf));
}