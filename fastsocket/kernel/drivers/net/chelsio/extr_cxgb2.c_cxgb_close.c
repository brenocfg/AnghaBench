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
struct port_info {struct cmac* mac; } ;
struct net_device {size_t if_port; struct adapter* ml_priv; } ;
struct cmac {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ stats_update_period; } ;
struct adapter {int open_device_map; int /*<<< orphan*/  work_lock; TYPE_2__ params; int /*<<< orphan*/  napi; struct port_info* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable ) (struct cmac*,int) ;} ;

/* Variables and functions */
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int PORT_MASK ; 
 int /*<<< orphan*/  cancel_mac_stats_update (struct adapter*) ; 
 int /*<<< orphan*/  clear_bit (size_t,int*) ; 
 int /*<<< orphan*/  cxgb_down (struct adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cmac*,int) ; 

__attribute__((used)) static int cxgb_close(struct net_device *dev)
{
	struct adapter *adapter = dev->ml_priv;
	struct port_info *p = &adapter->port[dev->if_port];
	struct cmac *mac = p->mac;

	netif_stop_queue(dev);
	napi_disable(&adapter->napi);
	mac->ops->disable(mac, MAC_DIRECTION_TX | MAC_DIRECTION_RX);
	netif_carrier_off(dev);

	clear_bit(dev->if_port, &adapter->open_device_map);
	if (adapter->params.stats_update_period &&
	    !(adapter->open_device_map & PORT_MASK)) {
		/* Stop statistics accumulation. */
		smp_mb__after_clear_bit();
		spin_lock(&adapter->work_lock);   /* sync with update task */
		spin_unlock(&adapter->work_lock);
		cancel_mac_stats_update(adapter);
	}

	if (!adapter->open_device_map)
		cxgb_down(adapter);
	return 0;
}