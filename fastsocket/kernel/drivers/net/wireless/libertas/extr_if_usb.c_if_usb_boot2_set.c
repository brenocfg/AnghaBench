#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lbs_private {struct if_usb_card* card; } ;
struct if_usb_card {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {struct lbs_private* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_CMD_UPDATE_BOOT2 ; 
 int if_usb_prog_firmware (struct if_usb_card*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t if_usb_boot2_set(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct lbs_private *priv = to_net_dev(dev)->ml_priv;
	struct if_usb_card *cardp = priv->card;
	int ret;

	ret = if_usb_prog_firmware(cardp, buf, BOOT_CMD_UPDATE_BOOT2);
	if (ret == 0)
		return count;

	return ret;
}