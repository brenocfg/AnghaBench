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
struct rfcomm_dev {int /*<<< orphan*/  dst; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  baswap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* batostr (int /*<<< orphan*/ *) ; 
 struct rfcomm_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t show_address(struct device *tty_dev, struct device_attribute *attr, char *buf)
{
	struct rfcomm_dev *dev = dev_get_drvdata(tty_dev);
	bdaddr_t bdaddr;
	baswap(&bdaddr, &dev->dst);
	return sprintf(buf, "%s\n", batostr(&bdaddr));
}