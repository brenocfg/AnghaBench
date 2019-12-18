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

/* Variables and functions */
 int /*<<< orphan*/  ASSABET_BCR_LCD_ON ; 
 int /*<<< orphan*/  ASSABET_BCR_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSABET_BCR_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void assabet_lcd_power(int on)
{
#ifndef ASSABET_PAL_VIDEO
	if (on) {
		ASSABET_BCR_set(ASSABET_BCR_LCD_ON);
		udelay(500);
	} else
#endif
		ASSABET_BCR_clear(ASSABET_BCR_LCD_ON);
}