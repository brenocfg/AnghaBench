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
typedef  scalar_t__ u32 ;
struct tun_struct {int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUN_NOCHECKSUM ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int tun_set_rx_csum(struct net_device *dev, u32 data)
{
	struct tun_struct *tun = netdev_priv(dev);
	if (data)
		tun->flags &= ~TUN_NOCHECKSUM;
	else
		tun->flags |= TUN_NOCHECKSUM;
	return 0;
}