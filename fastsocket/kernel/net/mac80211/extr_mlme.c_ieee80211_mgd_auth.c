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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_if_managed {int /*<<< orphan*/  mtx; struct ieee80211_mgd_auth_data* auth_data; int /*<<< orphan*/  bssid; scalar_t__ associated; scalar_t__ assoc_data; } ;
struct TYPE_5__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; TYPE_1__ u; struct ieee80211_local* local; } ;
struct ieee80211_mgd_auth_data {size_t data_len; int key_len; TYPE_3__* bss; int /*<<< orphan*/  done; int /*<<< orphan*/  algorithm; int /*<<< orphan*/ * key; int /*<<< orphan*/  key_idx; int /*<<< orphan*/ * data; void* sae_status; void* sae_trans; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; int /*<<< orphan*/  wep_tx_tfm; } ;
struct cfg80211_auth_request {int auth_type; int sae_data_len; int ie_len; int key_len; TYPE_3__* bss; scalar_t__ key; int /*<<< orphan*/  key_idx; scalar_t__ ie; scalar_t__ sae_data; } ;
typedef  int /*<<< orphan*/  frame_buf ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_7__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BSSID ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_DEAUTH_FRAME_LEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  NL80211_AUTHTYPE_FT 132 
#define  NL80211_AUTHTYPE_NETWORK_EAP 131 
#define  NL80211_AUTHTYPE_OPEN_SYSTEM 130 
#define  NL80211_AUTHTYPE_SAE 129 
#define  NL80211_AUTHTYPE_SHARED_KEY 128 
 int /*<<< orphan*/  WLAN_AUTH_FT ; 
 int /*<<< orphan*/  WLAN_AUTH_LEAP ; 
 int /*<<< orphan*/  WLAN_AUTH_OPEN ; 
 int /*<<< orphan*/  WLAN_AUTH_SAE ; 
 int /*<<< orphan*/  WLAN_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  WLAN_REASON_UNSPECIFIED ; 
 int /*<<< orphan*/  __cfg80211_send_deauth (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfg80211_ref_bss (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_destroy_auth_data (struct ieee80211_sub_if_data*,int) ; 
 int ieee80211_prep_connection (struct ieee80211_sub_if_data*,TYPE_3__*,int) ; 
 int ieee80211_probe_auth (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_set_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_mgd_auth_data*) ; 
 struct ieee80211_mgd_auth_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_info_destroy_addr (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

int ieee80211_mgd_auth(struct ieee80211_sub_if_data *sdata,
		       struct cfg80211_auth_request *req)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_mgd_auth_data *auth_data;
	u16 auth_alg;
	int err;

	/* prepare auth data structure */

	switch (req->auth_type) {
	case NL80211_AUTHTYPE_OPEN_SYSTEM:
		auth_alg = WLAN_AUTH_OPEN;
		break;
	case NL80211_AUTHTYPE_SHARED_KEY:
		if (IS_ERR(local->wep_tx_tfm))
			return -EOPNOTSUPP;
		auth_alg = WLAN_AUTH_SHARED_KEY;
		break;
	case NL80211_AUTHTYPE_FT:
		auth_alg = WLAN_AUTH_FT;
		break;
	case NL80211_AUTHTYPE_NETWORK_EAP:
		auth_alg = WLAN_AUTH_LEAP;
		break;
	case NL80211_AUTHTYPE_SAE:
		auth_alg = WLAN_AUTH_SAE;
		break;
	default:
		return -EOPNOTSUPP;
	}

	auth_data = kzalloc(sizeof(*auth_data) + req->sae_data_len +
			    req->ie_len, GFP_KERNEL);
	if (!auth_data)
		return -ENOMEM;

	auth_data->bss = req->bss;

	if (req->sae_data_len >= 4) {
		__le16 *pos = (__le16 *) req->sae_data;
		auth_data->sae_trans = le16_to_cpu(pos[0]);
		auth_data->sae_status = le16_to_cpu(pos[1]);
		memcpy(auth_data->data, req->sae_data + 4,
		       req->sae_data_len - 4);
		auth_data->data_len += req->sae_data_len - 4;
	}

	if (req->ie && req->ie_len) {
		memcpy(&auth_data->data[auth_data->data_len],
		       req->ie, req->ie_len);
		auth_data->data_len += req->ie_len;
	}

	if (req->key && req->key_len) {
		auth_data->key_len = req->key_len;
		auth_data->key_idx = req->key_idx;
		memcpy(auth_data->key, req->key, req->key_len);
	}

	auth_data->algorithm = auth_alg;

	/* try to authenticate/probe */

	mutex_lock(&ifmgd->mtx);

	if ((ifmgd->auth_data && !ifmgd->auth_data->done) ||
	    ifmgd->assoc_data) {
		err = -EBUSY;
		goto err_free;
	}

	if (ifmgd->auth_data)
		ieee80211_destroy_auth_data(sdata, false);

	/* prep auth_data so we don't go into idle on disassoc */
	ifmgd->auth_data = auth_data;

	if (ifmgd->associated) {
		u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       WLAN_REASON_UNSPECIFIED,
				       false, frame_buf);

		__cfg80211_send_deauth(sdata->dev, frame_buf,
				       sizeof(frame_buf));
	}

	sdata_info(sdata, "authenticate with %pM\n", req->bss->bssid);

	err = ieee80211_prep_connection(sdata, req->bss, false);
	if (err)
		goto err_clear;

	err = ieee80211_probe_auth(sdata);
	if (err) {
		sta_info_destroy_addr(sdata, req->bss->bssid);
		goto err_clear;
	}

	/* hold our own reference */
	cfg80211_ref_bss(local->hw.wiphy, auth_data->bss);
	err = 0;
	goto out_unlock;

 err_clear:
	memset(ifmgd->bssid, 0, ETH_ALEN);
	ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BSSID);
	ifmgd->auth_data = NULL;
 err_free:
	kfree(auth_data);
 out_unlock:
	mutex_unlock(&ifmgd->mtx);

	return err;
}