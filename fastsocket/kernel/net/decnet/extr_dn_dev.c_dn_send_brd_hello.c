#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ dn_ptr; } ;
struct dn_ifaddr {int dummy; } ;
struct TYPE_2__ {scalar_t__ forwarding; } ;
struct dn_dev {TYPE_1__ parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_send_endnode_hello (struct net_device*,struct dn_ifaddr*) ; 
 int /*<<< orphan*/  dn_send_router_hello (struct net_device*,struct dn_ifaddr*) ; 

__attribute__((used)) static void dn_send_brd_hello(struct net_device *dev, struct dn_ifaddr *ifa)
{
	struct dn_dev *dn_db = (struct dn_dev *)dev->dn_ptr;

	if (dn_db->parms.forwarding == 0)
		dn_send_endnode_hello(dev, ifa);
	else
		dn_send_router_hello(dev, ifa);
}