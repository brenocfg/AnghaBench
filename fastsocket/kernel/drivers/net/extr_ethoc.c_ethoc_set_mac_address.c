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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ethoc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_ADDR0 ; 
 int /*<<< orphan*/  MAC_ADDR1 ; 
 int /*<<< orphan*/  ethoc_write (struct ethoc*,int /*<<< orphan*/ ,int) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ethoc_set_mac_address(struct net_device *dev, void *addr)
{
	struct ethoc *priv = netdev_priv(dev);
	u8 *mac = (u8 *)addr;

	ethoc_write(priv, MAC_ADDR0, (mac[2] << 24) | (mac[3] << 16) |
				     (mac[4] <<  8) | (mac[5] <<  0));
	ethoc_write(priv, MAC_ADDR1, (mac[0] <<  8) | (mac[1] <<  0));

	return 0;
}