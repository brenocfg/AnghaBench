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
struct TYPE_4__ {int /*<<< orphan*/  broadcast_mode; } ;
struct TYPE_3__ {scalar_t__ link_type; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  conf_mutex; TYPE_2__ options; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ QETH_LINK_TYPE_HSTR ; 
 scalar_t__ QETH_LINK_TYPE_LANE_TR ; 
 int /*<<< orphan*/  QETH_TR_BROADCAST_ALLRINGS ; 
 int /*<<< orphan*/  QETH_TR_BROADCAST_LOCAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_broadcast_mode_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	char *tmp;
	int rc = 0;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	if ((card->state != CARD_STATE_DOWN) &&
	    (card->state != CARD_STATE_RECOVER)) {
		rc = -EPERM;
		goto out;
	}

	if (!((card->info.link_type == QETH_LINK_TYPE_HSTR) ||
	      (card->info.link_type == QETH_LINK_TYPE_LANE_TR))) {
		rc = -EINVAL;
		goto out;
	}

	tmp = strsep((char **) &buf, "\n");

	if (!strcmp(tmp, "local"))
		card->options.broadcast_mode = QETH_TR_BROADCAST_LOCAL;
	else if (!strcmp(tmp, "all_rings"))
		card->options.broadcast_mode = QETH_TR_BROADCAST_ALLRINGS;
	else
		rc = -EINVAL;
out:
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}