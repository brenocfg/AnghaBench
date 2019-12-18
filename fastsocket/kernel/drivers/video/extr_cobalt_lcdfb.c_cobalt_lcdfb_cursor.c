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
typedef  int u32 ;
struct TYPE_3__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; } ;
struct TYPE_4__ {int dx; int dy; } ;
struct fb_cursor {int set; scalar_t__ enable; TYPE_2__ image; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_CUR_SETPOS 128 
 int /*<<< orphan*/  LCD_CURSOR_OFF ; 
 int /*<<< orphan*/  LCD_CURSOR_ON ; 
 int /*<<< orphan*/  LCD_TEXT_POS (int) ; 
 int LCD_XRES_MAX ; 
 int LCD_YRES_MAX ; 
 int lcd_busy_wait (struct fb_info*) ; 
 int /*<<< orphan*/  lcd_write_control (struct fb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cobalt_lcdfb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
	u32 x, y;
	int retval;

	switch (cursor->set) {
	case FB_CUR_SETPOS:
		x = cursor->image.dx;
		y = cursor->image.dy;
		if (x >= LCD_XRES_MAX || y >= LCD_YRES_MAX)
			return -EINVAL;

		retval = lcd_busy_wait(info);
		if (retval < 0)
			return retval;

		lcd_write_control(info,
				  LCD_TEXT_POS(info->fix.line_length * y + x));
		break;
	default:
		return -EINVAL;
	}

	retval = lcd_busy_wait(info);
	if (retval < 0)
		return retval;

	if (cursor->enable)
		lcd_write_control(info, LCD_CURSOR_ON);
	else
		lcd_write_control(info, LCD_CURSOR_OFF);

	return 0;
}