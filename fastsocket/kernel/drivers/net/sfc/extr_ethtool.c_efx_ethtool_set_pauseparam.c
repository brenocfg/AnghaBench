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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct efx_nic {scalar_t__ link_advertising; int wanted_fc; int /*<<< orphan*/  mac_lock; TYPE_2__* type; int /*<<< orphan*/  net_dev; TYPE_1__* phy_op; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reconfigure_mac ) (struct efx_nic*) ;} ;
struct TYPE_3__ {int (* reconfigure ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int EFX_FC_AUTO ; 
 int EFX_FC_RX ; 
 int EFX_FC_TX ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 scalar_t__ EFX_WORKAROUND_11482 (struct efx_nic*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RESET_TYPE_INVISIBLE ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_link_set_wanted_fc (struct efx_nic*,int) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_drain_tx_fifo (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_reconfigure_xmac (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_start_nic_stats (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_stop_nic_stats (struct efx_nic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub2 (struct efx_nic*) ; 

__attribute__((used)) static int efx_ethtool_set_pauseparam(struct net_device *net_dev,
				      struct ethtool_pauseparam *pause)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	u8 wanted_fc, old_fc;
	u32 old_adv;
	bool reset;
	int rc = 0;

	mutex_lock(&efx->mac_lock);

	wanted_fc = ((pause->rx_pause ? EFX_FC_RX : 0) |
		     (pause->tx_pause ? EFX_FC_TX : 0) |
		     (pause->autoneg ? EFX_FC_AUTO : 0));

	if ((wanted_fc & EFX_FC_TX) && !(wanted_fc & EFX_FC_RX)) {
		netif_dbg(efx, drv, efx->net_dev,
			  "Flow control unsupported: tx ON rx OFF\n");
		rc = -EINVAL;
		goto out;
	}

	if ((wanted_fc & EFX_FC_AUTO) && !efx->link_advertising) {
		netif_dbg(efx, drv, efx->net_dev,
			  "Autonegotiation is disabled\n");
		rc = -EINVAL;
		goto out;
	}

	/* TX flow control may automatically turn itself off if the
	 * link partner (intermittently) stops responding to pause
	 * frames. There isn't any indication that this has happened,
	 * so the best we do is leave it up to the user to spot this
	 * and fix it be cycling transmit flow control on this end. */
	reset = (wanted_fc & EFX_FC_TX) && !(efx->wanted_fc & EFX_FC_TX);
	if (EFX_WORKAROUND_11482(efx) && reset) {
		if (efx_nic_rev(efx) == EFX_REV_FALCON_B0) {
			/* Recover by resetting the EM block */
			falcon_stop_nic_stats(efx);
			falcon_drain_tx_fifo(efx);
			falcon_reconfigure_xmac(efx);
			falcon_start_nic_stats(efx);
		} else {
			/* Schedule a reset to recover */
			efx_schedule_reset(efx, RESET_TYPE_INVISIBLE);
		}
	}

	old_adv = efx->link_advertising;
	old_fc = efx->wanted_fc;
	efx_link_set_wanted_fc(efx, wanted_fc);
	if (efx->link_advertising != old_adv ||
	    (efx->wanted_fc ^ old_fc) & EFX_FC_AUTO) {
		rc = efx->phy_op->reconfigure(efx);
		if (rc) {
			netif_err(efx, drv, efx->net_dev,
				  "Unable to advertise requested flow "
				  "control setting\n");
			goto out;
		}
	}

	/* Reconfigure the MAC. The PHY *may* generate a link state change event
	 * if the user just changed the advertised capabilities, but there's no
	 * harm doing this twice */
	efx->type->reconfigure_mac(efx);

out:
	mutex_unlock(&efx->mac_lock);

	return rc;
}