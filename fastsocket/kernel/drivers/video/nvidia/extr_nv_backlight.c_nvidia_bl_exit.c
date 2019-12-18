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
struct nvidia_par {int /*<<< orphan*/  pci_dev; } ;
struct fb_info {struct backlight_device* bl_dev; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 
 struct fb_info* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

void nvidia_bl_exit(struct nvidia_par *par)
{
	struct fb_info *info = pci_get_drvdata(par->pci_dev);
	struct backlight_device *bd = info->bl_dev;

	backlight_device_unregister(bd);
	printk("nvidia: Backlight unloaded\n");
}