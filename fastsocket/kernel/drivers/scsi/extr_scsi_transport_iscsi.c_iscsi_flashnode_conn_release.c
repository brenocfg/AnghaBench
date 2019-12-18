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
struct iscsi_bus_flash_conn {struct iscsi_bus_flash_conn* link_local_ipv6_addr; struct iscsi_bus_flash_conn* redirect_ipaddr; struct iscsi_bus_flash_conn* ipaddress; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iscsi_bus_flash_conn* iscsi_dev_to_flash_conn (struct device*) ; 
 int /*<<< orphan*/  kfree (struct iscsi_bus_flash_conn*) ; 

__attribute__((used)) static void iscsi_flashnode_conn_release(struct device *dev)
{
	struct iscsi_bus_flash_conn *fnode_conn = iscsi_dev_to_flash_conn(dev);

	kfree(fnode_conn->ipaddress);
	kfree(fnode_conn->redirect_ipaddr);
	kfree(fnode_conn->link_local_ipv6_addr);
	kfree(fnode_conn);
}