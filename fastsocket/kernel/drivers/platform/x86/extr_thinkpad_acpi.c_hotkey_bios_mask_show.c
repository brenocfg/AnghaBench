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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int hotkey_orig_mask ; 
 int /*<<< orphan*/  printk_deprecated_attribute (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t hotkey_bios_mask_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	printk_deprecated_attribute("hotkey_bios_mask",
			"This attribute is useless.");
	return snprintf(buf, PAGE_SIZE, "0x%08x\n", hotkey_orig_mask);
}