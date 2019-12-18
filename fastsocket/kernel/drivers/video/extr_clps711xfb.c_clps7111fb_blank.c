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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EDB_PD1_LCD_DC_DC_EN ; 
 int EDB_PD2_LCDEN ; 
 int EDB_PD3_LCDBL ; 
 int /*<<< orphan*/  PDDR ; 
 int /*<<< orphan*/  SYSCON1 ; 
 int SYSCON1_LCDEN ; 
 int clps_readb (int /*<<< orphan*/ ) ; 
 int clps_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_edb7211 () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int clps7111fb_blank(int blank, struct fb_info *info)
{
    	if (blank) {
		if (machine_is_edb7211()) {
			/* Turn off the LCD backlight. */
			clps_writeb(clps_readb(PDDR) & ~EDB_PD3_LCDBL, PDDR);

			/* Power off the LCD DC-DC converter. */
			clps_writeb(clps_readb(PDDR) & ~EDB_PD1_LCD_DC_DC_EN, PDDR);

			/* Delay for a little while (half a second). */
			udelay(100);

			/* Power off the LCD panel. */
			clps_writeb(clps_readb(PDDR) & ~EDB_PD2_LCDEN, PDDR);

			/* Power off the LCD controller. */
			clps_writel(clps_readl(SYSCON1) & ~SYSCON1_LCDEN, 
					SYSCON1);
		}
	} else {
		if (machine_is_edb7211()) {
			/* Power up the LCD controller. */
			clps_writel(clps_readl(SYSCON1) | SYSCON1_LCDEN,
					SYSCON1);

			/* Power up the LCD panel. */
			clps_writeb(clps_readb(PDDR) | EDB_PD2_LCDEN, PDDR);

			/* Delay for a little while. */
			udelay(100);

			/* Power up the LCD DC-DC converter. */
			clps_writeb(clps_readb(PDDR) | EDB_PD1_LCD_DC_DC_EN,
					PDDR);

			/* Turn on the LCD backlight. */
			clps_writeb(clps_readb(PDDR) | EDB_PD3_LCDBL, PDDR);
		}
	}
	return 0;
}