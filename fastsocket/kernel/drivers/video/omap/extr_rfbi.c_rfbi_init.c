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
struct omapfb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int l4_khz; int /*<<< orphan*/  dss_ick; int /*<<< orphan*/  base; struct omapfb_device* fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQ_FRAMEMASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RFBI_BASE ; 
 int /*<<< orphan*/  RFBI_CONFIG0 ; 
 int /*<<< orphan*/  RFBI_CONTROL ; 
 int /*<<< orphan*/  RFBI_DATA_CYCLE1_0 ; 
 int /*<<< orphan*/  RFBI_REVISION ; 
 int /*<<< orphan*/  RFBI_SYSCONFIG ; 
 int /*<<< orphan*/  RFBI_SYSSTATUS ; 
 int /*<<< orphan*/  SZ_1K ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_dispc_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 TYPE_1__ rfbi ; 
 int /*<<< orphan*/  rfbi_dma_callback ; 
 int /*<<< orphan*/  rfbi_enable_clocks (int) ; 
 int rfbi_get_clocks () ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rfbi_init(struct omapfb_device *fbdev)
{
	u32 l;
	int r;

	rfbi.fbdev = fbdev;
	rfbi.base = ioremap(RFBI_BASE, SZ_1K);
	if (!rfbi.base) {
		dev_err(fbdev->dev, "can't ioremap RFBI\n");
		return -ENOMEM;
	}

	if ((r = rfbi_get_clocks()) < 0)
		return r;
	rfbi_enable_clocks(1);

	rfbi.l4_khz = clk_get_rate(rfbi.dss_ick) / 1000;

	/* Reset */
	rfbi_write_reg(RFBI_SYSCONFIG, 1 << 1);
	while (!(rfbi_read_reg(RFBI_SYSSTATUS) & (1 << 0)));

	l = rfbi_read_reg(RFBI_SYSCONFIG);
	/* Enable autoidle and smart-idle */
	l |= (1 << 0) | (2 << 3);
	rfbi_write_reg(RFBI_SYSCONFIG, l);

	/* 16-bit interface, ITE trigger mode, 16-bit data */
	l = (0x03 << 0) | (0x00 << 2) | (0x01 << 5) | (0x02 << 7);
	l |= (0 << 9) | (1 << 20) | (1 << 21);
	rfbi_write_reg(RFBI_CONFIG0, l);

	rfbi_write_reg(RFBI_DATA_CYCLE1_0, 0x00000010);

	l = rfbi_read_reg(RFBI_CONTROL);
	/* Select CS0, clear bypass mode */
	l = (0x01 << 2);
	rfbi_write_reg(RFBI_CONTROL, l);

	r = omap_dispc_request_irq(DISPC_IRQ_FRAMEMASK, rfbi_dma_callback,
				   NULL);
	if (r < 0) {
		dev_err(fbdev->dev, "can't get DISPC irq\n");
		rfbi_enable_clocks(0);
		return r;
	}

	l = rfbi_read_reg(RFBI_REVISION);
	pr_info("omapfb: RFBI version %d.%d initialized\n",
		(l >> 4) & 0x0f, l & 0x0f);

	rfbi_enable_clocks(0);

	return 0;
}