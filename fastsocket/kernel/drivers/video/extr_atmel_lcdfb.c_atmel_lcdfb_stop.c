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
struct atmel_lcdfb_info {int dummy; } ;

/* Variables and functions */
 int ATMEL_LCDC_DMABUSY ; 
 int /*<<< orphan*/  ATMEL_LCDC_DMACON ; 
 int /*<<< orphan*/  atmel_lcdfb_stop_nowait (struct atmel_lcdfb_info*) ; 
 int lcdc_readl (struct atmel_lcdfb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void atmel_lcdfb_stop(struct atmel_lcdfb_info *sinfo)
{
	atmel_lcdfb_stop_nowait(sinfo);

	/* Wait for DMA engine to become idle... */
	while (lcdc_readl(sinfo, ATMEL_LCDC_DMACON) & ATMEL_LCDC_DMABUSY)
		msleep(10);
}