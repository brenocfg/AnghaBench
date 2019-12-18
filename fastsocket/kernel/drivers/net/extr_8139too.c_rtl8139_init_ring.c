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
struct rtl8139_private {int /*<<< orphan*/ * tx_bufs; int /*<<< orphan*/ ** tx_buf; scalar_t__ dirty_tx; scalar_t__ cur_tx; scalar_t__ cur_rx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NUM_TX_DESC ; 
 int TX_BUF_SIZE ; 
 struct rtl8139_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void rtl8139_init_ring (struct net_device *dev)
{
	struct rtl8139_private *tp = netdev_priv(dev);
	int i;

	tp->cur_rx = 0;
	tp->cur_tx = 0;
	tp->dirty_tx = 0;

	for (i = 0; i < NUM_TX_DESC; i++)
		tp->tx_buf[i] = &tp->tx_bufs[i * TX_BUF_SIZE];
}