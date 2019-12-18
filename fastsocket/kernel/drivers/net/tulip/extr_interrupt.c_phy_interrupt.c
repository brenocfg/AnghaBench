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
struct tulip_private {int csr12_shadow; scalar_t__ base_addr; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSR12 ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct tulip_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tulip_check_duplex (struct net_device*) ; 

__attribute__((used)) static inline unsigned int phy_interrupt (struct net_device *dev)
{
#ifdef __hppa__
	struct tulip_private *tp = netdev_priv(dev);
	int csr12 = ioread32(tp->base_addr + CSR12) & 0xff;

	if (csr12 != tp->csr12_shadow) {
		/* ack interrupt */
		iowrite32(csr12 | 0x02, tp->base_addr + CSR12);
		tp->csr12_shadow = csr12;
		/* do link change stuff */
		spin_lock(&tp->lock);
		tulip_check_duplex(dev);
		spin_unlock(&tp->lock);
		/* clear irq ack bit */
		iowrite32(csr12 & ~0x02, tp->base_addr + CSR12);

		return 1;
	}
#endif

	return 0;
}