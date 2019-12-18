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
struct qset_params {int /*<<< orphan*/ * txq_size; int /*<<< orphan*/  jumbo_size; int /*<<< orphan*/  rspq_size; int /*<<< orphan*/  fl_size; } ;
struct port_info {size_t first_qset; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_mini_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_jumbo_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct TYPE_3__ {struct qset_params* qset; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RX_BUFFERS ; 
 int /*<<< orphan*/  MAX_RX_JUMBO_BUFFERS ; 
 int /*<<< orphan*/  MAX_TXQ_ENTRIES ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void get_sge_param(struct net_device *dev, struct ethtool_ringparam *e)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	const struct qset_params *q = &adapter->params.sge.qset[pi->first_qset];

	e->rx_max_pending = MAX_RX_BUFFERS;
	e->rx_jumbo_max_pending = MAX_RX_JUMBO_BUFFERS;
	e->tx_max_pending = MAX_TXQ_ENTRIES;

	e->rx_pending = q->fl_size;
	e->rx_mini_pending = q->rspq_size;
	e->rx_jumbo_pending = q->jumbo_size;
	e->tx_pending = q->txq_size[0];
}