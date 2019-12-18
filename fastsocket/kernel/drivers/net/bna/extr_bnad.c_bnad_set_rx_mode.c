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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int flags; } ;
struct bnad {int cfg_flags; int /*<<< orphan*/  bna_lock; TYPE_1__* rx_info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rx; } ;

/* Variables and functions */
 int BNAD_CF_ALLMULTI ; 
 int BNAD_CF_PROMISC ; 
 int /*<<< orphan*/  BNAD_RXMODE_PROMISC_DEFAULT ; 
 int /*<<< orphan*/  BNA_RXMODE_ALLMULTI ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  bna_rx_mcast_listset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_rx_mode_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bnad_bcast_addr ; 
 int /*<<< orphan*/  bnad_netdev_mc_list_get (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int netdev_mc_count (struct net_device*) ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
bnad_set_rx_mode(struct net_device *netdev)
{
	struct bnad *bnad = netdev_priv(netdev);
	u32	new_mask, valid_mask;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);

	new_mask = valid_mask = 0;

	if (netdev->flags & IFF_PROMISC) {
		if (!(bnad->cfg_flags & BNAD_CF_PROMISC)) {
			new_mask = BNAD_RXMODE_PROMISC_DEFAULT;
			valid_mask = BNAD_RXMODE_PROMISC_DEFAULT;
			bnad->cfg_flags |= BNAD_CF_PROMISC;
		}
	} else {
		if (bnad->cfg_flags & BNAD_CF_PROMISC) {
			new_mask = ~BNAD_RXMODE_PROMISC_DEFAULT;
			valid_mask = BNAD_RXMODE_PROMISC_DEFAULT;
			bnad->cfg_flags &= ~BNAD_CF_PROMISC;
		}
	}

	if (netdev->flags & IFF_ALLMULTI) {
		if (!(bnad->cfg_flags & BNAD_CF_ALLMULTI)) {
			new_mask |= BNA_RXMODE_ALLMULTI;
			valid_mask |= BNA_RXMODE_ALLMULTI;
			bnad->cfg_flags |= BNAD_CF_ALLMULTI;
		}
	} else {
		if (bnad->cfg_flags & BNAD_CF_ALLMULTI) {
			new_mask &= ~BNA_RXMODE_ALLMULTI;
			valid_mask |= BNA_RXMODE_ALLMULTI;
			bnad->cfg_flags &= ~BNAD_CF_ALLMULTI;
		}
	}

	if (bnad->rx_info[0].rx == NULL)
		goto unlock;

	bna_rx_mode_set(bnad->rx_info[0].rx, new_mask, valid_mask, NULL);

	if (!netdev_mc_empty(netdev)) {
		u8 *mcaddr_list;
		int mc_count = netdev_mc_count(netdev);

		/* Index 0 holds the broadcast address */
		mcaddr_list =
			kzalloc((mc_count + 1) * ETH_ALEN,
				GFP_ATOMIC);
		if (!mcaddr_list)
			goto unlock;

		memcpy(&mcaddr_list[0], &bnad_bcast_addr[0], ETH_ALEN);

		/* Copy rest of the MC addresses */
		bnad_netdev_mc_list_get(netdev, mcaddr_list);

		bna_rx_mcast_listset(bnad->rx_info[0].rx, mc_count + 1,
					mcaddr_list, NULL);

		/* Should we enable BNAD_CF_ALLMULTI for err != 0 ? */
		kfree(mcaddr_list);
	}
unlock:
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}