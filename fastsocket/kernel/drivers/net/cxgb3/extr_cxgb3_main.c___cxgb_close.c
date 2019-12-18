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
struct TYPE_5__ {scalar_t__ offset; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct port_info {int /*<<< orphan*/  port_id; TYPE_2__ mac; TYPE_3__ phy; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int open_device_map; int /*<<< orphan*/  tdev; int /*<<< orphan*/  adap_check_task; int /*<<< orphan*/  work_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* power_down ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 scalar_t__ A_XGM_INT_STATUS ; 
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int /*<<< orphan*/  OFFLOAD_PORT_DOWN ; 
 int PORT_MASK ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cxgb3_event_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_down (struct adapter*,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  t3_mac_disable (TYPE_2__*,int) ; 
 int /*<<< orphan*/  t3_port_intr_disable (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  t3_xgm_intr_disable (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cxgb_close(struct net_device *dev, int on_wq)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	
	if (!adapter->open_device_map)
		return 0;

	/* Stop link fault interrupts */
	t3_xgm_intr_disable(adapter, pi->port_id);
	t3_read_reg(adapter, A_XGM_INT_STATUS + pi->mac.offset);

	t3_port_intr_disable(adapter, pi->port_id);
	netif_tx_stop_all_queues(dev);
	pi->phy.ops->power_down(&pi->phy, 1);
	netif_carrier_off(dev);
	t3_mac_disable(&pi->mac, MAC_DIRECTION_TX | MAC_DIRECTION_RX);

	spin_lock_irq(&adapter->work_lock);	/* sync with update task */
	clear_bit(pi->port_id, &adapter->open_device_map);
	spin_unlock_irq(&adapter->work_lock);

	if (!(adapter->open_device_map & PORT_MASK))
		cancel_delayed_work_sync(&adapter->adap_check_task);

	if (!adapter->open_device_map)
		cxgb_down(adapter, on_wq);

	cxgb3_event_notify(&adapter->tdev, OFFLOAD_PORT_DOWN, pi->port_id);
	return 0;
}