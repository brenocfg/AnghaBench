#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qeth_perf_stats {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_6__ {int /*<<< orphan*/  initial_tx_packets; int /*<<< orphan*/  initial_rx_packets; } ;
struct TYPE_4__ {int performance_stats; } ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; TYPE_2__ stats; TYPE_3__ perf_stats; TYPE_1__ options; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static ssize_t qeth_dev_performance_stats_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	char *tmp;
	int i, rc = 0;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	i = simple_strtoul(buf, &tmp, 16);
	if ((i == 0) || (i == 1)) {
		if (i == card->options.performance_stats)
			goto out;;
		card->options.performance_stats = i;
		if (i == 0)
			memset(&card->perf_stats, 0,
				sizeof(struct qeth_perf_stats));
		card->perf_stats.initial_rx_packets = card->stats.rx_packets;
		card->perf_stats.initial_tx_packets = card->stats.tx_packets;
	} else
		rc = -EINVAL;
out:
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}