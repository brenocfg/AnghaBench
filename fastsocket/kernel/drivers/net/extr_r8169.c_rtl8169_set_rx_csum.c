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
typedef  int /*<<< orphan*/  u32 ;
struct rtl8169_private {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rtl8169_set_rx_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_set_rx_csum(struct net_device *dev, u32 data)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl_lock_work(tp);
	__rtl8169_set_rx_csum(dev, data);
	rtl_unlock_work(tp);

	return 0;
}