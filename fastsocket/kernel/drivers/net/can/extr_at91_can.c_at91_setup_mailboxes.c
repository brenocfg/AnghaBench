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
struct net_device {int dummy; } ;
struct at91_priv {scalar_t__ rx_next; scalar_t__ tx_echo; scalar_t__ tx_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_MB_MODE_RX ; 
 int /*<<< orphan*/  AT91_MB_MODE_RX_OVRWR ; 
 int /*<<< orphan*/  AT91_MB_MODE_TX ; 
 unsigned int AT91_MB_RX_FIRST ; 
 unsigned int AT91_MB_RX_LAST ; 
 unsigned int AT91_MB_TX_FIRST ; 
 unsigned int AT91_MB_TX_LAST ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_mb_mode (struct at91_priv*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mb_mode_prio (struct at91_priv*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91_setup_mailboxes(struct net_device *dev)
{
	struct at91_priv *priv = netdev_priv(dev);
	unsigned int i;

	/*
	 * The first 12 mailboxes are used as a reception FIFO. The
	 * last mailbox is configured with overwrite option. The
	 * overwrite flag indicates a FIFO overflow.
	 */
	for (i = AT91_MB_RX_FIRST; i < AT91_MB_RX_LAST; i++)
		set_mb_mode(priv, i, AT91_MB_MODE_RX);
	set_mb_mode(priv, AT91_MB_RX_LAST, AT91_MB_MODE_RX_OVRWR);

	/* The last 4 mailboxes are used for transmitting. */
	for (i = AT91_MB_TX_FIRST; i <= AT91_MB_TX_LAST; i++)
		set_mb_mode_prio(priv, i, AT91_MB_MODE_TX, 0);

	/* Reset tx and rx helper pointers */
	priv->tx_next = priv->tx_echo = priv->rx_next = 0;
}