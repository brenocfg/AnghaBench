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
typedef  int /*<<< orphan*/  rtl8150_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSCR ; 
 short CSCR_LINK_STATUS ; 
 int /*<<< orphan*/  get_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,short*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static void set_carrier(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	short tmp;

	get_registers(dev, CSCR, 2, &tmp);
	if (tmp & CSCR_LINK_STATUS)
		netif_carrier_on(netdev);
	else
		netif_carrier_off(netdev);
}