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
struct TYPE_4__ {scalar_t__ broadcast_mode; } ;
struct TYPE_3__ {scalar_t__ link_type; } ;
struct qeth_card {TYPE_2__ options; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ QETH_LINK_TYPE_HSTR ; 
 scalar_t__ QETH_LINK_TYPE_LANE_TR ; 
 scalar_t__ QETH_TR_BROADCAST_ALLRINGS ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_broadcast_mode_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct qeth_card *card = dev_get_drvdata(dev);

	if (!card)
		return -EINVAL;

	if (!((card->info.link_type == QETH_LINK_TYPE_HSTR) ||
	      (card->info.link_type == QETH_LINK_TYPE_LANE_TR)))
		return sprintf(buf, "n/a\n");

	return sprintf(buf, "%s\n", (card->options.broadcast_mode ==
				     QETH_TR_BROADCAST_ALLRINGS)?
		       "all rings":"local");
}