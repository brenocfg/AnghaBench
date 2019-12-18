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
struct at91_priv {int reg_sr; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_IDR ; 
 int /*<<< orphan*/  AT91_IMR ; 
 int AT91_IRQ_ERR_FRAME ; 
 int AT91_IRQ_MB_RX ; 
 int AT91_IRQ_MB_TX ; 
 int /*<<< orphan*/  AT91_SR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  at91_irq_err (struct net_device*) ; 
 int /*<<< orphan*/  at91_irq_tx (struct net_device*,int) ; 
 int at91_read (struct at91_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_write (struct at91_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t at91_irq(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct at91_priv *priv = netdev_priv(dev);
	irqreturn_t handled = IRQ_NONE;
	u32 reg_sr, reg_imr;

	reg_sr = at91_read(priv, AT91_SR);
	reg_imr = at91_read(priv, AT91_IMR);

	/* Ignore masked interrupts */
	reg_sr &= reg_imr;
	if (!reg_sr)
		goto exit;

	handled = IRQ_HANDLED;

	/* Receive or error interrupt? -> napi */
	if (reg_sr & (AT91_IRQ_MB_RX | AT91_IRQ_ERR_FRAME)) {
		/*
		 * The error bits are clear on read,
		 * save for later use.
		 */
		priv->reg_sr = reg_sr;
		at91_write(priv, AT91_IDR,
			   AT91_IRQ_MB_RX | AT91_IRQ_ERR_FRAME);
		napi_schedule(&priv->napi);
	}

	/* Transmission complete interrupt */
	if (reg_sr & AT91_IRQ_MB_TX)
		at91_irq_tx(dev, reg_sr);

	at91_irq_err(dev);

 exit:
	return handled;
}