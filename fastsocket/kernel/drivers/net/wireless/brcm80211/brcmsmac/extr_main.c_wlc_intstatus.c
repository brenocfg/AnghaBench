#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct brcms_hardware {struct bcma_device* d11core; } ;
struct brcms_c_info {int macintmask; int defmacintmask; struct brcms_hardware* hw; } ;
struct bcma_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int intstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int) ; 
 int DEF_RXINTMASK ; 
 int MI_DMAINT ; 
 size_t RX_FIFO ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ brcms_deviceremoved (struct brcms_c_info*) ; 
 TYPE_1__* intctrlregs ; 
 int macintmask ; 
 int /*<<< orphan*/  trace_brcms_macintstatus (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static inline u32 wlc_intstatus(struct brcms_c_info *wlc, bool in_isr)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	struct bcma_device *core = wlc_hw->d11core;
	u32 macintstatus, mask;

	/* macintstatus includes a DMA interrupt summary bit */
	macintstatus = bcma_read32(core, D11REGOFFS(macintstatus));
	mask = in_isr ? wlc->macintmask : wlc->defmacintmask;

	trace_brcms_macintstatus(&core->dev, in_isr, macintstatus, mask);

	/* detect cardbus removed, in power down(suspend) and in reset */
	if (brcms_deviceremoved(wlc))
		return -1;

	/* brcms_deviceremoved() succeeds even when the core is still resetting,
	 * handle that case here.
	 */
	if (macintstatus == 0xffffffff)
		return 0;

	/* defer unsolicited interrupts */
	macintstatus &= mask;

	/* if not for us */
	if (macintstatus == 0)
		return 0;

	/* turn off the interrupts */
	bcma_write32(core, D11REGOFFS(macintmask), 0);
	(void)bcma_read32(core, D11REGOFFS(macintmask));
	wlc->macintmask = 0;

	/* clear device interrupts */
	bcma_write32(core, D11REGOFFS(macintstatus), macintstatus);

	/* MI_DMAINT is indication of non-zero intstatus */
	if (macintstatus & MI_DMAINT)
		/*
		 * only fifo interrupt enabled is I_RI in
		 * RX_FIFO. If MI_DMAINT is set, assume it
		 * is set and clear the interrupt.
		 */
		bcma_write32(core, D11REGOFFS(intctrlregs[RX_FIFO].intstatus),
			     DEF_RXINTMASK);

	return macintstatus;
}