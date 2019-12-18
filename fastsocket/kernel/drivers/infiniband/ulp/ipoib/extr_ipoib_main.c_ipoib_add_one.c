#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  list; } ;
struct ib_device {scalar_t__ node_type; int phys_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  IS_ERR (struct net_device*) ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 scalar_t__ RDMA_TRANSPORT_IB ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct list_head*) ; 
 struct net_device* ipoib_add_port (char*,struct ib_device*,int) ; 
 int /*<<< orphan*/  ipoib_client ; 
 struct list_head* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ rdma_node_get_transport (scalar_t__) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int) ; 

__attribute__((used)) static void ipoib_add_one(struct ib_device *device)
{
	struct list_head *dev_list;
	struct net_device *dev;
	struct ipoib_dev_priv *priv;
	int s, e, p;

	if (rdma_node_get_transport(device->node_type) != RDMA_TRANSPORT_IB)
		return;

	dev_list = kmalloc(sizeof *dev_list, GFP_KERNEL);
	if (!dev_list)
		return;

	INIT_LIST_HEAD(dev_list);

	if (device->node_type == RDMA_NODE_IB_SWITCH) {
		s = 0;
		e = 0;
	} else {
		s = 1;
		e = device->phys_port_cnt;
	}

	for (p = s; p <= e; ++p) {
		if (rdma_port_get_link_layer(device, p) != IB_LINK_LAYER_INFINIBAND)
			continue;
		dev = ipoib_add_port("ib%d", device, p);
		if (!IS_ERR(dev)) {
			priv = netdev_priv(dev);
			list_add_tail(&priv->list, dev_list);
		}
	}

	ib_set_client_data(device, &ipoib_client, dev_list);
}