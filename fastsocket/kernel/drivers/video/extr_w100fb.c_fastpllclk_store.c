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
struct w100fb_par {int fastpll_mode; } ;
struct fb_info {struct w100fb_par* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  calc_hsync (struct w100fb_par*) ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  w100_init_clocks (struct w100fb_par*) ; 

__attribute__((used)) static ssize_t fastpllclk_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct fb_info *info = dev_get_drvdata(dev);
	struct w100fb_par *par=info->par;

	if (simple_strtoul(buf, NULL, 10) > 0) {
		par->fastpll_mode=1;
		printk("w100fb: Using fast system clock (if possible)\n");
	} else {
		par->fastpll_mode=0;
		printk("w100fb: Using normal system clock\n");
	}

	w100_init_clocks(par);
	calc_hsync(par);

	return count;
}