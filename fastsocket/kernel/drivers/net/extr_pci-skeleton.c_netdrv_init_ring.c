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
struct netdrv_private {int /*<<< orphan*/ * tx_bufs; int /*<<< orphan*/ ** tx_buf; TYPE_1__* tx_info; int /*<<< orphan*/  dirty_tx; int /*<<< orphan*/  cur_tx; scalar_t__ cur_rx; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ mapping; int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int NUM_TX_DESC ; 
 int TX_BUF_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct netdrv_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netdrv_init_ring (struct net_device *dev)
{
	struct netdrv_private *tp = netdev_priv(dev);
	int i;

	DPRINTK ("ENTER\n");

	tp->cur_rx = 0;
	atomic_set (&tp->cur_tx, 0);
	atomic_set (&tp->dirty_tx, 0);

	for (i = 0; i < NUM_TX_DESC; i++) {
		tp->tx_info[i].skb = NULL;
		tp->tx_info[i].mapping = 0;
		tp->tx_buf[i] = &tp->tx_bufs[i * TX_BUF_SIZE];
	}

	DPRINTK ("EXIT\n");
}