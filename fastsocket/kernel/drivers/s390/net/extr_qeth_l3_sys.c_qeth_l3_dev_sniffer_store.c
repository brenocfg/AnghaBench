#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  buf_count; } ;
struct TYPE_9__ {TYPE_3__ init_pool; } ;
struct TYPE_7__ {scalar_t__ cq; unsigned long sniffer; } ;
struct TYPE_10__ {int qdioac2; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  conf_mutex; TYPE_4__ qdio; TYPE_2__ options; TYPE_5__ ssqd; TYPE_1__ info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int /*<<< orphan*/  QETH_IN_BUF_COUNT_MAX ; 
 int QETH_SNIFF_AVAIL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdio_get_ssqd_desc (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  qeth_realloc_buffer_pool (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_sniffer_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	int rc = 0;
	unsigned long i;

	if (!card)
		return -EINVAL;

	if (card->info.type != QETH_CARD_TYPE_IQD)
		return -EPERM;
	if (card->options.cq == QETH_CQ_ENABLED)
		return -EPERM;

	mutex_lock(&card->conf_mutex);
	if ((card->state != CARD_STATE_DOWN) &&
	    (card->state != CARD_STATE_RECOVER)) {
		rc = -EPERM;
		goto out;
	}

	rc = strict_strtoul(buf, 16, &i);
	if (rc) {
		rc = -EINVAL;
		goto out;
	}
	switch (i) {
	case 0:
		card->options.sniffer = i;
		break;
	case 1:
		qdio_get_ssqd_desc(CARD_DDEV(card), &card->ssqd);
		if (card->ssqd.qdioac2 & QETH_SNIFF_AVAIL) {
			card->options.sniffer = i;
			if (card->qdio.init_pool.buf_count !=
					QETH_IN_BUF_COUNT_MAX)
				qeth_realloc_buffer_pool(card,
					QETH_IN_BUF_COUNT_MAX);
			break;
		} else
			rc = -EPERM;
	default:   /* fall through */
		rc = -EINVAL;
	}
out:
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}