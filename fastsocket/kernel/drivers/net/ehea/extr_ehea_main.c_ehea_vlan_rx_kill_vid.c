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
typedef  scalar_t__ u64 ;
struct net_device {int dummy; } ;
struct hcp_ehea_port_cb1 {scalar_t__* vlan_filter; } ;
struct ehea_port {int /*<<< orphan*/  logical_port_id; int /*<<< orphan*/  vgrp; struct ehea_adapter* adapter; } ;
struct ehea_adapter {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  H_PORT_CB1 ; 
 int /*<<< orphan*/  H_PORT_CB1_ALL ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 scalar_t__ ehea_h_modify_ehea_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hcp_ehea_port_cb1*) ; 
 scalar_t__ ehea_h_query_ehea_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hcp_ehea_port_cb1*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vlan_group_set_device (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehea_vlan_rx_kill_vid(struct net_device *dev, unsigned short vid)
{
	struct ehea_port *port = netdev_priv(dev);
	struct ehea_adapter *adapter = port->adapter;
	struct hcp_ehea_port_cb1 *cb1;
	int index;
	u64 hret;

	vlan_group_set_device(port->vgrp, vid, NULL);

	cb1 = (void *)get_zeroed_page(GFP_KERNEL);
	if (!cb1) {
		ehea_error("no mem for cb1");
		goto out;
	}

	hret = ehea_h_query_ehea_port(adapter->handle, port->logical_port_id,
				      H_PORT_CB1, H_PORT_CB1_ALL, cb1);
	if (hret != H_SUCCESS) {
		ehea_error("query_ehea_port failed");
		goto out;
	}

	index = (vid / 64);
	cb1->vlan_filter[index] &= ~((u64)(0x8000000000000000 >> (vid & 0x3F)));

	hret = ehea_h_modify_ehea_port(adapter->handle, port->logical_port_id,
				       H_PORT_CB1, H_PORT_CB1_ALL, cb1);
	if (hret != H_SUCCESS)
		ehea_error("modify_ehea_port failed");
out:
	free_page((unsigned long)cb1);
	return;
}