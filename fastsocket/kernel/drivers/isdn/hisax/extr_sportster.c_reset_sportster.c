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
struct TYPE_3__ {int /*<<< orphan*/  res_irq; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ spt; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPORTSTER_RESET ; 
 scalar_t__ SPORTSTER_RES_IRQ ; 
 int /*<<< orphan*/  byteout (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void
reset_sportster(struct IsdnCardState *cs)
{
	cs->hw.spt.res_irq |= SPORTSTER_RESET; /* Reset On */
	byteout(cs->hw.spt.cfg_reg + SPORTSTER_RES_IRQ, cs->hw.spt.res_irq);
	mdelay(10);
	cs->hw.spt.res_irq &= ~SPORTSTER_RESET; /* Reset Off */
	byteout(cs->hw.spt.cfg_reg + SPORTSTER_RES_IRQ, cs->hw.spt.res_irq);
	mdelay(10);
}