#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ieee80211_if_managed {int /*<<< orphan*/  mtx; struct ieee80211_mgd_auth_data* auth_data; } ;
struct TYPE_5__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; struct ieee80211_local* local; } ;
struct ieee80211_mgd_auth_data {scalar_t__ tries; int expected_transaction; int sae_trans; int sae_status; int timeout_started; scalar_t__ timeout; TYPE_3__* bss; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  algorithm; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
struct TYPE_7__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; scalar_t__ proberesp_ies; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ IEEE80211_AUTH_MAX_TRIES ; 
 scalar_t__ IEEE80211_AUTH_TIMEOUT ; 
 scalar_t__ IEEE80211_AUTH_TIMEOUT_LONG ; 
 int IEEE80211_HW_REPORTS_TX_ACK_STATUS ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int IEEE80211_TX_INTFL_MLME_CONN_TX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WLAN_AUTH_SAE ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int /*<<< orphan*/  cfg80211_unlink_bss (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  drv_mgd_prepare_tx (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/ * ieee80211_bss_get_ie (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_auth (struct ieee80211_sub_if_data*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_send_probe_req (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ round_jiffies_up (scalar_t__) ; 
 int /*<<< orphan*/  run_again (struct ieee80211_if_managed*,scalar_t__) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int ieee80211_probe_auth(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_mgd_auth_data *auth_data = ifmgd->auth_data;
	u32 tx_flags = 0;

	lockdep_assert_held(&ifmgd->mtx);

	if (WARN_ON_ONCE(!auth_data))
		return -EINVAL;

	auth_data->tries++;

	if (auth_data->tries > IEEE80211_AUTH_MAX_TRIES) {
		sdata_info(sdata, "authentication with %pM timed out\n",
			   auth_data->bss->bssid);

		/*
		 * Most likely AP is not in the range so remove the
		 * bss struct for that AP.
		 */
		cfg80211_unlink_bss(local->hw.wiphy, auth_data->bss);

		return -ETIMEDOUT;
	}

	drv_mgd_prepare_tx(local, sdata);

	if (auth_data->bss->proberesp_ies) {
		u16 trans = 1;
		u16 status = 0;

		sdata_info(sdata, "send auth to %pM (try %d/%d)\n",
			   auth_data->bss->bssid, auth_data->tries,
			   IEEE80211_AUTH_MAX_TRIES);

		auth_data->expected_transaction = 2;

		if (auth_data->algorithm == WLAN_AUTH_SAE) {
			trans = auth_data->sae_trans;
			status = auth_data->sae_status;
			auth_data->expected_transaction = trans;
		}

		if (local->hw.flags & IEEE80211_HW_REPORTS_TX_ACK_STATUS)
			tx_flags = IEEE80211_TX_CTL_REQ_TX_STATUS |
				   IEEE80211_TX_INTFL_MLME_CONN_TX;

		ieee80211_send_auth(sdata, trans, auth_data->algorithm, status,
				    auth_data->data, auth_data->data_len,
				    auth_data->bss->bssid,
				    auth_data->bss->bssid, NULL, 0, 0,
				    tx_flags);
	} else {
		const u8 *ssidie;

		sdata_info(sdata, "direct probe to %pM (try %d/%i)\n",
			   auth_data->bss->bssid, auth_data->tries,
			   IEEE80211_AUTH_MAX_TRIES);

		rcu_read_lock();
		ssidie = ieee80211_bss_get_ie(auth_data->bss, WLAN_EID_SSID);
		if (!ssidie) {
			rcu_read_unlock();
			return -EINVAL;
		}
		/*
		 * Direct probe is sent to broadcast address as some APs
		 * will not answer to direct packet in unassociated state.
		 */
		ieee80211_send_probe_req(sdata, NULL, ssidie + 2, ssidie[1],
					 NULL, 0, (u32) -1, true, 0,
					 auth_data->bss->channel, false);
		rcu_read_unlock();
	}

	if (tx_flags == 0) {
		auth_data->timeout = jiffies + IEEE80211_AUTH_TIMEOUT;
		auth_data->timeout_started = true;
		run_again(ifmgd, auth_data->timeout);
	} else {
		auth_data->timeout =
			round_jiffies_up(jiffies + IEEE80211_AUTH_TIMEOUT_LONG);
		auth_data->timeout_started = true;
		run_again(ifmgd, auth_data->timeout);
	}

	return 0;
}