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
struct qeth_card {int /*<<< orphan*/  conf_mutex; TYPE_1__ options; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum qeth_large_send_types { ____Placeholder_qeth_large_send_types } qeth_large_send_types ;

/* Variables and functions */
 int EINVAL ; 
 int QETH_LARGE_SEND_NO ; 
 int QETH_LARGE_SEND_TSO ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qeth_l3_set_large_send (struct qeth_card*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_large_send_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	enum qeth_large_send_types type;
	int rc = 0;
	char *tmp;

	if (!card)
		return -EINVAL;
	tmp = strsep((char **) &buf, "\n");
	if (!strcmp(tmp, "no"))
		type = QETH_LARGE_SEND_NO;
	else if (!strcmp(tmp, "TSO"))
		type = QETH_LARGE_SEND_TSO;
	else
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	if (card->options.large_send != type)
		rc = qeth_l3_set_large_send(card, type);
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}