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
struct TYPE_3__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/ * sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct TYPE_4__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
struct lbs_private {scalar_t__ connect_status; scalar_t__ psstate; TYPE_2__ curbssparams; scalar_t__ numSNRNF; scalar_t__ nextSNRNF; int /*<<< orphan*/ * rawNF; int /*<<< orphan*/ * rawSNR; int /*<<< orphan*/ * RSSI; int /*<<< orphan*/ * NF; int /*<<< orphan*/ * SNR; scalar_t__ tx_pending_len; int /*<<< orphan*/ * currenttxskb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int ETH_ALEN ; 
 int IW_ESSID_MAX_SIZE ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 scalar_t__ LBS_DISCONNECTED ; 
 scalar_t__ PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_ps_wakeup (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void lbs_mac_event_disconnected(struct lbs_private *priv)
{
	union iwreq_data wrqu;

	if (priv->connect_status != LBS_CONNECTED)
		return;

	lbs_deb_enter(LBS_DEB_ASSOC);

	memset(wrqu.ap_addr.sa_data, 0x00, ETH_ALEN);
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	/*
	 * Cisco AP sends EAP failure and de-auth in less than 0.5 ms.
	 * It causes problem in the Supplicant
	 */

	msleep_interruptible(1000);
	wireless_send_event(priv->dev, SIOCGIWAP, &wrqu, NULL);

	/* report disconnect to upper layer */
	netif_stop_queue(priv->dev);
	netif_carrier_off(priv->dev);

	/* Free Tx and Rx packets */
	kfree_skb(priv->currenttxskb);
	priv->currenttxskb = NULL;
	priv->tx_pending_len = 0;

	/* reset SNR/NF/RSSI values */
	memset(priv->SNR, 0x00, sizeof(priv->SNR));
	memset(priv->NF, 0x00, sizeof(priv->NF));
	memset(priv->RSSI, 0x00, sizeof(priv->RSSI));
	memset(priv->rawSNR, 0x00, sizeof(priv->rawSNR));
	memset(priv->rawNF, 0x00, sizeof(priv->rawNF));
	priv->nextSNRNF = 0;
	priv->numSNRNF = 0;
	priv->connect_status = LBS_DISCONNECTED;

	/* Clear out associated SSID and BSSID since connection is
	 * no longer valid.
	 */
	memset(&priv->curbssparams.bssid, 0, ETH_ALEN);
	memset(&priv->curbssparams.ssid, 0, IW_ESSID_MAX_SIZE);
	priv->curbssparams.ssid_len = 0;

	if (priv->psstate != PS_STATE_FULL_POWER) {
		/* make firmware to exit PS mode */
		lbs_deb_cmd("disconnected, so exit PS mode\n");
		lbs_ps_wakeup(priv, 0);
	}
	lbs_deb_leave(LBS_DEB_ASSOC);
}