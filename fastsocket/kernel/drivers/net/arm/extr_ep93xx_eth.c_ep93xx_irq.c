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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ep93xx_priv {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REG_INTEN ; 
 int /*<<< orphan*/  REG_INTEN_TX ; 
 int /*<<< orphan*/  REG_INTSTSC ; 
 int REG_INTSTS_RX ; 
 int REG_INTSTS_TX ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ep93xx_tx_complete (struct net_device*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct ep93xx_priv* netdev_priv (struct net_device*) ; 
 int rdl (struct ep93xx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrl (struct ep93xx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ep93xx_irq(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct ep93xx_priv *ep = netdev_priv(dev);
	u32 status;

	status = rdl(ep, REG_INTSTSC);
	if (status == 0)
		return IRQ_NONE;

	if (status & REG_INTSTS_RX) {
		spin_lock(&ep->rx_lock);
		if (likely(napi_schedule_prep(&ep->napi))) {
			wrl(ep, REG_INTEN, REG_INTEN_TX);
			__napi_schedule(&ep->napi);
		}
		spin_unlock(&ep->rx_lock);
	}

	if (status & REG_INTSTS_TX)
		ep93xx_tx_complete(dev);

	return IRQ_HANDLED;
}