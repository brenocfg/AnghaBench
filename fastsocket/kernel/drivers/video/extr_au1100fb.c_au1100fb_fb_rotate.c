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
struct fb_info {int dummy; } ;
struct au1100fb_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int lcd_control; } ;

/* Variables and functions */
 int LCD_CONTROL_GO ; 
 int LCD_CONTROL_SM_BIT ; 
 int LCD_CONTROL_SM_MASK ; 
 int /*<<< orphan*/  print_dbg (char*,struct fb_info*,int) ; 
 struct au1100fb_device* to_au1100fb_device (struct fb_info*) ; 

void au1100fb_fb_rotate(struct fb_info *fbi, int angle)
{
	struct au1100fb_device *fbdev = to_au1100fb_device(fbi);

	print_dbg("fb_rotate %p %d", fbi, angle);

	if (fbdev && (angle > 0) && !(angle % 90)) {

		fbdev->regs->lcd_control &= ~LCD_CONTROL_GO;

		fbdev->regs->lcd_control &= ~(LCD_CONTROL_SM_MASK);
		fbdev->regs->lcd_control |= ((angle/90) << LCD_CONTROL_SM_BIT);

		fbdev->regs->lcd_control |= LCD_CONTROL_GO;
	}
}