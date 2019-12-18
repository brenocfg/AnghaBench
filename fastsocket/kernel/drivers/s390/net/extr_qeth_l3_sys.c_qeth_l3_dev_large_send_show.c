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
struct TYPE_2__ {int large_send; } ;
struct qeth_card {TYPE_1__ options; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  QETH_LARGE_SEND_NO 129 
#define  QETH_LARGE_SEND_TSO 128 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_large_send_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct qeth_card *card = dev_get_drvdata(dev);

	if (!card)
		return -EINVAL;

	switch (card->options.large_send) {
	case QETH_LARGE_SEND_NO:
		return sprintf(buf, "%s\n", "no");
	case QETH_LARGE_SEND_TSO:
		return sprintf(buf, "%s\n", "TSO");
	default:
		return sprintf(buf, "%s\n", "N/A");
	}
}