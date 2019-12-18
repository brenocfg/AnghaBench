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
struct TYPE_2__ {int invert6; } ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; TYPE_1__ ipato; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_ipato_invert6_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	char *tmp;
	int rc = 0;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	tmp = strsep((char **) &buf, "\n");
	if (!strcmp(tmp, "toggle")) {
		card->ipato.invert6 = (card->ipato.invert6)? 0 : 1;
	} else if (!strcmp(tmp, "1")) {
		card->ipato.invert6 = 1;
	} else if (!strcmp(tmp, "0")) {
		card->ipato.invert6 = 0;
	} else
		rc = -EINVAL;
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}