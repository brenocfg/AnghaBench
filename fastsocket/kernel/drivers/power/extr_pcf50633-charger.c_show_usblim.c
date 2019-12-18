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
typedef  scalar_t__ u8 ;
struct pcf50633_mbc {int /*<<< orphan*/  pcf; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ PCF50633_MBCC7_USB_1000mA ; 
 scalar_t__ PCF50633_MBCC7_USB_100mA ; 
 scalar_t__ PCF50633_MBCC7_USB_500mA ; 
 scalar_t__ PCF50633_MBCC7_USB_MASK ; 
 int /*<<< orphan*/  PCF50633_REG_MBCC7 ; 
 struct pcf50633_mbc* dev_get_drvdata (struct device*) ; 
 scalar_t__ pcf50633_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t
show_usblim(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct pcf50633_mbc *mbc = dev_get_drvdata(dev);
	u8 usblim = pcf50633_reg_read(mbc->pcf, PCF50633_REG_MBCC7) &
						PCF50633_MBCC7_USB_MASK;
	unsigned int ma;

	if (usblim == PCF50633_MBCC7_USB_1000mA)
		ma = 1000;
	else if (usblim == PCF50633_MBCC7_USB_500mA)
		ma = 500;
	else if (usblim == PCF50633_MBCC7_USB_100mA)
		ma = 100;
	else
		ma = 0;

	return sprintf(buf, "%u\n", ma);
}