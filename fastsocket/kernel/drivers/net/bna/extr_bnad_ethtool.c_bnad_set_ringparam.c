#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;
struct bnad {scalar_t__ rxq_depth; scalar_t__ txq_depth; int num_rx; int cfg_flags; int num_tx; int /*<<< orphan*/  conf_mutex; TYPE_2__* tx_info; int /*<<< orphan*/  bna_lock; TYPE_1__* rx_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct TYPE_3__ {scalar_t__ rx; } ;

/* Variables and functions */
 int BNAD_CF_ALLMULTI ; 
 int BNAD_CF_PROMISC ; 
 scalar_t__ BNAD_MAX_RXQ_DEPTH ; 
 scalar_t__ BNAD_MAX_TXQ_DEPTH ; 
 scalar_t__ BNAD_MIN_Q_DEPTH ; 
 int /*<<< orphan*/  BNA_POWER_OF_2 (scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bnad_destroy_rx (struct bnad*,int) ; 
 int /*<<< orphan*/  bnad_destroy_tx (struct bnad*,int) ; 
 int /*<<< orphan*/  bnad_enable_default_bcast (struct bnad*) ; 
 int /*<<< orphan*/  bnad_mac_addr_set_locked (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_restore_vlans (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_set_rx_mode (struct net_device*) ; 
 int bnad_setup_rx (struct bnad*,int) ; 
 int bnad_setup_tx (struct bnad*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bnad_set_ringparam(struct net_device *netdev,
		   struct ethtool_ringparam *ringparam)
{
	int i, current_err, err = 0;
	struct bnad *bnad = netdev_priv(netdev);
	unsigned long flags;

	mutex_lock(&bnad->conf_mutex);
	if (ringparam->rx_pending == bnad->rxq_depth &&
	    ringparam->tx_pending == bnad->txq_depth) {
		mutex_unlock(&bnad->conf_mutex);
		return 0;
	}

	if (ringparam->rx_pending < BNAD_MIN_Q_DEPTH ||
	    ringparam->rx_pending > BNAD_MAX_RXQ_DEPTH ||
	    !BNA_POWER_OF_2(ringparam->rx_pending)) {
		mutex_unlock(&bnad->conf_mutex);
		return -EINVAL;
	}
	if (ringparam->tx_pending < BNAD_MIN_Q_DEPTH ||
	    ringparam->tx_pending > BNAD_MAX_TXQ_DEPTH ||
	    !BNA_POWER_OF_2(ringparam->tx_pending)) {
		mutex_unlock(&bnad->conf_mutex);
		return -EINVAL;
	}

	if (ringparam->rx_pending != bnad->rxq_depth) {
		bnad->rxq_depth = ringparam->rx_pending;
		if (!netif_running(netdev)) {
			mutex_unlock(&bnad->conf_mutex);
			return 0;
		}

		for (i = 0; i < bnad->num_rx; i++) {
			if (!bnad->rx_info[i].rx)
				continue;
			bnad_destroy_rx(bnad, i);
			current_err = bnad_setup_rx(bnad, i);
			if (current_err && !err)
				err = current_err;
		}

		if (!err && bnad->rx_info[0].rx) {
			/* restore rx configuration */
			bnad_restore_vlans(bnad, 0);
			bnad_enable_default_bcast(bnad);
			spin_lock_irqsave(&bnad->bna_lock, flags);
			bnad_mac_addr_set_locked(bnad, netdev->dev_addr);
			spin_unlock_irqrestore(&bnad->bna_lock, flags);
			bnad->cfg_flags &= ~(BNAD_CF_ALLMULTI |
					     BNAD_CF_PROMISC);
			bnad_set_rx_mode(netdev);
		}
	}
	if (ringparam->tx_pending != bnad->txq_depth) {
		bnad->txq_depth = ringparam->tx_pending;
		if (!netif_running(netdev)) {
			mutex_unlock(&bnad->conf_mutex);
			return 0;
		}

		for (i = 0; i < bnad->num_tx; i++) {
			if (!bnad->tx_info[i].tx)
				continue;
			bnad_destroy_tx(bnad, i);
			current_err = bnad_setup_tx(bnad, i);
			if (current_err && !err)
				err = current_err;
		}
	}

	mutex_unlock(&bnad->conf_mutex);
	return err;
}