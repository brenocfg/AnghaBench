#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct atmel_lcdfb_info {int guard_time; } ;

/* Variables and functions */
 int ATMEL_LCDC_BUSY ; 
 int /*<<< orphan*/  ATMEL_LCDC_DMACON ; 
 int ATMEL_LCDC_GUARDT_OFFSET ; 
 int /*<<< orphan*/  ATMEL_LCDC_PWRCON ; 
 int lcdc_readl (struct atmel_lcdfb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_writel (struct atmel_lcdfb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void atmel_lcdfb_stop_nowait(struct atmel_lcdfb_info *sinfo)
{
	/* Turn off the LCD controller and the DMA controller */
	lcdc_writel(sinfo, ATMEL_LCDC_PWRCON,
			sinfo->guard_time << ATMEL_LCDC_GUARDT_OFFSET);

	/* Wait for the LCDC core to become idle */
	while (lcdc_readl(sinfo, ATMEL_LCDC_PWRCON) & ATMEL_LCDC_BUSY)
		msleep(10);

	lcdc_writel(sinfo, ATMEL_LCDC_DMACON, 0);
}