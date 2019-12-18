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
struct sm501fb_info {scalar_t__ regs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum sm501_controller { ____Placeholder_sm501_controller } sm501_controller ;

/* Variables and functions */
 size_t EINVAL ; 
 int HEAD_CRT ; 
 int HEAD_PANEL ; 
 scalar_t__ SM501_DC_CRT_CONTROL ; 
 unsigned long SM501_DC_CRT_CONTROL_ENABLE ; 
 unsigned long SM501_DC_CRT_CONTROL_SEL ; 
 unsigned long SM501_DC_CRT_CONTROL_TE ; 
 struct sm501fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  sm501fb_sync_regs (struct sm501fb_info*) ; 
 scalar_t__ strnicmp (char const*,char*,int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static ssize_t sm501fb_crtsrc_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t len)
{
	struct sm501fb_info *info = dev_get_drvdata(dev);
	enum sm501_controller head;
	unsigned long ctrl;

	if (len < 1)
		return -EINVAL;

	if (strnicmp(buf, "crt", 3) == 0)
		head = HEAD_CRT;
	else if (strnicmp(buf, "panel", 5) == 0)
		head = HEAD_PANEL;
	else
		return -EINVAL;

	dev_info(dev, "setting crt source to head %d\n", head);

	ctrl = readl(info->regs + SM501_DC_CRT_CONTROL);

	if (head == HEAD_CRT) {
		ctrl |= SM501_DC_CRT_CONTROL_SEL;
		ctrl |= SM501_DC_CRT_CONTROL_ENABLE;
		ctrl |= SM501_DC_CRT_CONTROL_TE;
	} else {
		ctrl &= ~SM501_DC_CRT_CONTROL_SEL;
		ctrl &= ~SM501_DC_CRT_CONTROL_ENABLE;
		ctrl &= ~SM501_DC_CRT_CONTROL_TE;
	}

	writel(ctrl, info->regs + SM501_DC_CRT_CONTROL);
	sm501fb_sync_regs(info);

	return len;
}