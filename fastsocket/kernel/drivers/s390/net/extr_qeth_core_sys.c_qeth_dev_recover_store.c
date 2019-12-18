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
struct qeth_card {scalar_t__ state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ CARD_STATE_UP ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static ssize_t qeth_dev_recover_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	char *tmp;
	int i;

	if (!card)
		return -EINVAL;

	if (card->state != CARD_STATE_UP)
		return -EPERM;

	i = simple_strtoul(buf, &tmp, 16);
	if (i == 1)
		qeth_schedule_recovery(card);

	return count;
}