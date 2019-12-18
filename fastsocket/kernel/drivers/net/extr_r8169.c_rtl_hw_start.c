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
struct rtl8169_private {int /*<<< orphan*/  (* hw_start ) (struct net_device*) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl_irq_enable_all (struct rtl8169_private*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static void rtl_hw_start(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	tp->hw_start(dev);

	rtl_irq_enable_all(tp);
}