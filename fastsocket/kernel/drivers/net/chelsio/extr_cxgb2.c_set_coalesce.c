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
struct net_device {struct adapter* ml_priv; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rate_sample_interval; int /*<<< orphan*/  use_adaptive_rx_coalesce; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct TYPE_4__ {int /*<<< orphan*/  sample_interval_usecs; int /*<<< orphan*/  coalesce_enable; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct TYPE_3__ {TYPE_2__ sge; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  t1_sge_set_coalesce_params (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int set_coalesce(struct net_device *dev, struct ethtool_coalesce *c)
{
	struct adapter *adapter = dev->ml_priv;

	adapter->params.sge.rx_coalesce_usecs = c->rx_coalesce_usecs;
	adapter->params.sge.coalesce_enable = c->use_adaptive_rx_coalesce;
	adapter->params.sge.sample_interval_usecs = c->rate_sample_interval;
	t1_sge_set_coalesce_params(adapter->sge, &adapter->params.sge);
	return 0;
}