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
struct tmiofb_par {scalar_t__ lcr; } ;
struct tmio_fb_data {int /*<<< orphan*/  (* lcd_set_power ) (struct platform_device*,int) ;int /*<<< orphan*/  (* lcd_mode ) (struct platform_device*,struct fb_videomode*) ;} ;
struct TYPE_3__ {struct mfd_cell* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mfd_cell {struct tmio_fb_data* driver_data; } ;
struct fb_videomode {int hsync_len; int left_margin; int xres; int right_margin; int vsync_len; int upper_margin; int yres; int lower_margin; } ;
struct TYPE_4__ {int line_length; } ;
struct fb_info {TYPE_2__ fix; struct tmiofb_par* par; struct fb_videomode* mode; } ;

/* Variables and functions */
 scalar_t__ LCR_GDSAH ; 
 scalar_t__ LCR_GDSAL ; 
 scalar_t__ LCR_GM ; 
 scalar_t__ LCR_HDS ; 
 scalar_t__ LCR_HNP ; 
 scalar_t__ LCR_HSE ; 
 scalar_t__ LCR_HSS ; 
 scalar_t__ LCR_HT ; 
 scalar_t__ LCR_ILN ; 
 scalar_t__ LCR_LCDCC ; 
 scalar_t__ LCR_LCDCCRC ; 
 scalar_t__ LCR_MISC ; 
 scalar_t__ LCR_SP ; 
 scalar_t__ LCR_VCS ; 
 scalar_t__ LCR_VDS ; 
 scalar_t__ LCR_VHPCH ; 
 scalar_t__ LCR_VHPCL ; 
 scalar_t__ LCR_VHPN ; 
 scalar_t__ LCR_VSE ; 
 scalar_t__ LCR_VSS ; 
 scalar_t__ LCR_VT ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct platform_device*,struct fb_videomode*) ; 
 int /*<<< orphan*/  stub3 (struct platform_device*,int) ; 
 int /*<<< orphan*/  tmio_iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static void tmiofb_hw_mode(struct platform_device *dev)
{
	struct mfd_cell *cell = dev->dev.platform_data;
	struct tmio_fb_data *data = cell->driver_data;
	struct fb_info *info = platform_get_drvdata(dev);
	struct fb_videomode *mode = info->mode;
	struct tmiofb_par *par = info->par;
	unsigned int i;

	tmio_iowrite16(0, par->lcr + LCR_GM);
	data->lcd_set_power(dev, 0);
	tmio_iowrite16(0x0010, par->lcr + LCR_LCDCCRC);
	data->lcd_mode(dev, mode);
	data->lcd_set_power(dev, 1);

	tmio_iowrite16(info->fix.line_length, par->lcr + LCR_VHPN);
	tmio_iowrite16(0, par->lcr + LCR_GDSAH);
	tmio_iowrite16(0, par->lcr + LCR_GDSAL);
	tmio_iowrite16(info->fix.line_length >> 16, par->lcr + LCR_VHPCH);
	tmio_iowrite16(info->fix.line_length, par->lcr + LCR_VHPCL);
	tmio_iowrite16(i = 0, par->lcr + LCR_HSS);
	tmio_iowrite16(i += mode->hsync_len, par->lcr + LCR_HSE);
	tmio_iowrite16(i += mode->left_margin, par->lcr + LCR_HDS);
	tmio_iowrite16(i += mode->xres + mode->right_margin, par->lcr + LCR_HT);
	tmio_iowrite16(mode->xres, par->lcr + LCR_HNP);
	tmio_iowrite16(i = 0, par->lcr + LCR_VSS);
	tmio_iowrite16(i += mode->vsync_len, par->lcr + LCR_VSE);
	tmio_iowrite16(i += mode->upper_margin, par->lcr + LCR_VDS);
	tmio_iowrite16(i += mode->yres, par->lcr + LCR_ILN);
	tmio_iowrite16(i += mode->lower_margin, par->lcr + LCR_VT);
	tmio_iowrite16(3, par->lcr + LCR_MISC); /* RGB565 mode */
	tmio_iowrite16(1, par->lcr + LCR_GM); /* VRAM enable */
	tmio_iowrite16(0x4007, par->lcr + LCR_LCDCC);
	tmio_iowrite16(3, par->lcr + LCR_SP);  /* sync polarity */

	tmio_iowrite16(0x0010, par->lcr + LCR_LCDCCRC);
	msleep(5); /* wait for device to settle */
	tmio_iowrite16(0x0014, par->lcr + LCR_LCDCCRC); /* STOP_CKP */
	msleep(5); /* wait for device to settle */
	tmio_iowrite16(0x0015, par->lcr + LCR_LCDCCRC); /* STOP_CKP|SOFT_RESET*/
	tmio_iowrite16(0xfffa, par->lcr + LCR_VCS);
}