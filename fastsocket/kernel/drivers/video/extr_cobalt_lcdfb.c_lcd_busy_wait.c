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
typedef  int /*<<< orphan*/  u8 ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int /*<<< orphan*/  LCD_BUSY ; 
 int /*<<< orphan*/  lcd_read_control (struct fb_info*) ; 
 scalar_t__ msleep_interruptible (int) ; 

__attribute__((used)) static int lcd_busy_wait(struct fb_info *info)
{
	u8 val = 0;
	int timeout = 10, retval = 0;

	do {
		val = lcd_read_control(info);
		val &= LCD_BUSY;
		if (val != LCD_BUSY)
			break;

		if (msleep_interruptible(1))
			return -EINTR;

		timeout--;
	} while (timeout);

	if (val == LCD_BUSY)
		retval = -EBUSY;

	return retval;
}