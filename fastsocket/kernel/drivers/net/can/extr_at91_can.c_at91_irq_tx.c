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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct at91_priv {scalar_t__ tx_next; scalar_t__ tx_echo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_IDR ; 
 scalar_t__ AT91_MB_TX_FIRST ; 
 int /*<<< orphan*/  AT91_MSR (unsigned int) ; 
 int AT91_MSR_MABT ; 
 int AT91_MSR_MRDY ; 
 int AT91_NEXT_MASK ; 
 int at91_read (struct at91_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_write (struct at91_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,scalar_t__) ; 
 unsigned int get_tx_echo_mb (struct at91_priv*) ; 
 scalar_t__ likely (int) ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void at91_irq_tx(struct net_device *dev, u32 reg_sr)
{
	struct at91_priv *priv = netdev_priv(dev);
	u32 reg_msr;
	unsigned int mb;

	/* masking of reg_sr not needed, already done by at91_irq */

	for (/* nix */; (priv->tx_next - priv->tx_echo) > 0; priv->tx_echo++) {
		mb = get_tx_echo_mb(priv);

		/* no event in mailbox? */
		if (!(reg_sr & (1 << mb)))
			break;

		/* Disable irq for this TX mailbox */
		at91_write(priv, AT91_IDR, 1 << mb);

		/*
		 * only echo if mailbox signals us a transfer
		 * complete (MSR_MRDY). Otherwise it's a tansfer
		 * abort. "can_bus_off()" takes care about the skbs
		 * parked in the echo queue.
		 */
		reg_msr = at91_read(priv, AT91_MSR(mb));
		if (likely(reg_msr & AT91_MSR_MRDY &&
			   ~reg_msr & AT91_MSR_MABT)) {
			/* _NOTE_: substract AT91_MB_TX_FIRST offset from mb! */
			can_get_echo_skb(dev, mb - AT91_MB_TX_FIRST);
			dev->stats.tx_packets++;
		}
	}

	/*
	 * restart queue if we don't have a wrap around but restart if
	 * we get a TX int for the last can frame directly before a
	 * wrap around.
	 */
	if ((priv->tx_next & AT91_NEXT_MASK) != 0 ||
	    (priv->tx_echo & AT91_NEXT_MASK) == 0)
		netif_wake_queue(dev);
}