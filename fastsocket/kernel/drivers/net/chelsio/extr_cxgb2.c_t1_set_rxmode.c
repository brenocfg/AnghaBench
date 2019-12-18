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
struct t1_rx_mode {int /*<<< orphan*/  list; scalar_t__ idx; struct net_device* dev; } ;
struct net_device {size_t if_port; int /*<<< orphan*/  mc_list; struct adapter* ml_priv; } ;
struct cmac {TYPE_1__* ops; } ;
struct adapter {TYPE_2__* port; } ;
struct TYPE_4__ {struct cmac* mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_rx_mode ) (struct cmac*,struct t1_rx_mode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cmac*,struct t1_rx_mode*) ; 

__attribute__((used)) static void t1_set_rxmode(struct net_device *dev)
{
	struct adapter *adapter = dev->ml_priv;
	struct cmac *mac = adapter->port[dev->if_port].mac;
	struct t1_rx_mode rm;

	rm.dev = dev;
	rm.idx = 0;
	rm.list = dev->mc_list;
	mac->ops->set_rx_mode(mac, &rm);
}