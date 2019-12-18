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
struct rtl8169_private {int /*<<< orphan*/  mmio_addr; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  R8169_REGS_SIZE ; 
 int /*<<< orphan*/  memcpy_fromio (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8169_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			     void *p)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (regs->len > R8169_REGS_SIZE)
		regs->len = R8169_REGS_SIZE;

	rtl_lock_work(tp);
	memcpy_fromio(p, tp->mmio_addr, regs->len);
	rtl_unlock_work(tp);
}