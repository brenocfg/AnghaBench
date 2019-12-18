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
struct rtl8169_private {int /*<<< orphan*/  Rx_databuff; int /*<<< orphan*/  tx_skb; } ;
struct ring_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NUM_RX_DESC ; 
 int NUM_TX_DESC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_init_ring_indexes (struct rtl8169_private*) ; 
 int rtl8169_rx_fill (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_init_ring(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl8169_init_ring_indexes(tp);

	memset(tp->tx_skb, 0x0, NUM_TX_DESC * sizeof(struct ring_info));
	memset(tp->Rx_databuff, 0x0, NUM_RX_DESC * sizeof(void *));

	return rtl8169_rx_fill(tp);
}