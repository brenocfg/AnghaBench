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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cmdQ_size; int /*<<< orphan*/ * freelQ_size; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CMDQ_ENTRIES ; 
 int /*<<< orphan*/  MAX_RX_BUFFERS ; 
 int /*<<< orphan*/  MAX_RX_JUMBO_BUFFERS ; 
 scalar_t__ t1_is_T1B (struct adapter*) ; 

__attribute__((used)) static void get_sge_param(struct net_device *dev, struct ethtool_ringparam *e)
{
	struct adapter *adapter = dev->ml_priv;
	int jumbo_fl = t1_is_T1B(adapter) ? 1 : 0;

	e->rx_max_pending = MAX_RX_BUFFERS;
	e->rx_mini_max_pending = 0;
	e->rx_jumbo_max_pending = MAX_RX_JUMBO_BUFFERS;
	e->tx_max_pending = MAX_CMDQ_ENTRIES;

	e->rx_pending = adapter->params.sge.freelQ_size[!jumbo_fl];
	e->rx_mini_pending = 0;
	e->rx_jumbo_pending = adapter->params.sge.freelQ_size[jumbo_fl];
	e->tx_pending = adapter->params.sge.cmdQ_size[0];
}