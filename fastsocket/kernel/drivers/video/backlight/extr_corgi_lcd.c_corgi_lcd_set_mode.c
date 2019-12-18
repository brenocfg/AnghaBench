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
struct lcd_device {int /*<<< orphan*/  dev; } ;
struct fb_videomode {int xres; } ;
struct corgi_lcd {int mode; } ;

/* Variables and functions */
#define  CORGI_LCD_MODE_QVGA 129 
#define  CORGI_LCD_MODE_VGA 128 
 int /*<<< orphan*/  RESCTL_ADRS ; 
 int /*<<< orphan*/  RESCTL_QVGA ; 
 int /*<<< orphan*/  RESCTL_VGA ; 
 int /*<<< orphan*/  corgi_ssp_lcdtg_send (struct corgi_lcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct corgi_lcd* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcdtg_set_phadadj (struct corgi_lcd*,int) ; 

__attribute__((used)) static int corgi_lcd_set_mode(struct lcd_device *ld, struct fb_videomode *m)
{
	struct corgi_lcd *lcd = dev_get_drvdata(&ld->dev);
	int mode = CORGI_LCD_MODE_QVGA;

	if (m->xres == 640 || m->xres == 480)
		mode = CORGI_LCD_MODE_VGA;

	if (lcd->mode == mode)
		return 0;

	lcdtg_set_phadadj(lcd, mode);

	switch (mode) {
	case CORGI_LCD_MODE_VGA:
		corgi_ssp_lcdtg_send(lcd, RESCTL_ADRS, RESCTL_VGA);
		break;
	case CORGI_LCD_MODE_QVGA:
	default:
		corgi_ssp_lcdtg_send(lcd, RESCTL_ADRS, RESCTL_QVGA);
		break;
	}

	lcd->mode = mode;
	return 0;
}