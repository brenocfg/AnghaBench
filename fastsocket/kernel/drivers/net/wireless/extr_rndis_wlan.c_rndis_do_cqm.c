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
struct usbnet {int /*<<< orphan*/  net; } ;
struct rndis_wlan_private {int cqm_rssi_thold; scalar_t__ infra_mode; int last_cqm_event_rssi; int cqm_rssi_hyst; } ;
typedef  int s32 ;
typedef  enum nl80211_cqm_rssi_threshold_event { ____Placeholder_nl80211_cqm_rssi_threshold_event } nl80211_cqm_rssi_threshold_event ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NDIS_80211_INFRA_INFRA ; 
 int NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH ; 
 int NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW ; 
 int /*<<< orphan*/  cfg80211_cqm_rssi_notify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 

__attribute__((used)) static void rndis_do_cqm(struct usbnet *usbdev, s32 rssi)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	enum nl80211_cqm_rssi_threshold_event event;
	int thold, hyst, last_event;

	if (priv->cqm_rssi_thold >= 0 || rssi >= 0)
		return;
	if (priv->infra_mode != NDIS_80211_INFRA_INFRA)
		return;

	last_event = priv->last_cqm_event_rssi;
	thold = priv->cqm_rssi_thold;
	hyst = priv->cqm_rssi_hyst;

	if (rssi < thold && (last_event == 0 || rssi < last_event - hyst))
		event = NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW;
	else if (rssi > thold && (last_event == 0 || rssi > last_event + hyst))
		event = NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH;
	else
		return;

	priv->last_cqm_event_rssi = rssi;
	cfg80211_cqm_rssi_notify(usbdev->net, event, GFP_KERNEL);
}