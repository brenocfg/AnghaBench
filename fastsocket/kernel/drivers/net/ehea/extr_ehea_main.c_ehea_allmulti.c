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
struct ehea_port {int allmulti; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_DEREG_BCMC ; 
 int /*<<< orphan*/  H_REG_BCMC ; 
 int /*<<< orphan*/  ehea_drop_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 scalar_t__ ehea_multicast_reg_helper (struct ehea_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ehea_allmulti(struct net_device *dev, int enable)
{
	struct ehea_port *port = netdev_priv(dev);
	u64 hret;

	if (!port->allmulti) {
		if (enable) {
			/* Enable ALLMULTI */
			ehea_drop_multicast_list(dev);
			hret = ehea_multicast_reg_helper(port, 0, H_REG_BCMC);
			if (!hret)
				port->allmulti = 1;
			else
				ehea_error("failed enabling IFF_ALLMULTI");
		}
	} else {
		if (!enable) {
			/* Disable ALLMULTI */
			hret = ehea_multicast_reg_helper(port, 0, H_DEREG_BCMC);
			if (!hret)
				port->allmulti = 0;
			else
				ehea_error("failed disabling IFF_ALLMULTI");
		}
	}
}