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
typedef  int u_int ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;
struct dev_priv {int /*<<< orphan*/  timer; TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int CSR0_BABL ; 
 int CSR0_CERR ; 
 int CSR0_IENA ; 
 int CSR0_MERR ; 
 int CSR0_MISS ; 
 int CSR0_RINT ; 
 int CSR0_TINT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  am79c961_rx (struct net_device*,struct dev_priv*) ; 
 int /*<<< orphan*/  am79c961_tx (struct net_device*,struct dev_priv*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int read_rreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_rreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t
am79c961_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct dev_priv *priv = netdev_priv(dev);
	u_int status, n = 100;
	int handled = 0;

	do {
		status = read_rreg(dev->base_addr, CSR0);
		write_rreg(dev->base_addr, CSR0, status &
			   (CSR0_IENA|CSR0_TINT|CSR0_RINT|
			    CSR0_MERR|CSR0_MISS|CSR0_CERR|CSR0_BABL));

		if (status & CSR0_RINT) {
			handled = 1;
			am79c961_rx(dev, priv);
		}
		if (status & CSR0_TINT) {
			handled = 1;
			am79c961_tx(dev, priv);
		}
		if (status & CSR0_MISS) {
			handled = 1;
			priv->stats.rx_dropped ++;
		}
		if (status & CSR0_CERR) {
			handled = 1;
			mod_timer(&priv->timer, jiffies);
		}
	} while (--n && status & (CSR0_RINT | CSR0_TINT));

	return IRQ_RETVAL(handled);
}