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
struct usb_ov511 {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct usb_ov511* cd_to_ov (struct device*) ; 
 int /*<<< orphan*/  sensor_get_contrast (struct usb_ov511*,unsigned short*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned short) ; 

__attribute__((used)) static ssize_t show_contrast(struct device *cd,
			     struct device_attribute *attr, char *buf)
{
	struct usb_ov511 *ov = cd_to_ov(cd);
	unsigned short x;

	if (!ov->dev)
		return -ENODEV;
	sensor_get_contrast(ov, &x);
	return sprintf(buf, "%d\n", x >> 8);
}