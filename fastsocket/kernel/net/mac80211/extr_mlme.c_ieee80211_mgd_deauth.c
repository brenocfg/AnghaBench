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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_if_managed {int /*<<< orphan*/  mtx; TYPE_2__* associated; scalar_t__ auth_data; } ;
struct TYPE_3__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  local; TYPE_1__ u; } ;
struct cfg80211_deauth_request {int /*<<< orphan*/  reason_code; int /*<<< orphan*/  bssid; int /*<<< orphan*/  local_state_change; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int IEEE80211_DEAUTH_FRAME_LEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  __cfg80211_send_deauth (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drv_mgd_prepare_tx (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_destroy_auth_data (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_send_deauth_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_set_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ieee80211_mgd_deauth(struct ieee80211_sub_if_data *sdata,
			 struct cfg80211_deauth_request *req)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];
	bool tx = !req->local_state_change;
	bool report_frame = false;

	mutex_lock(&ifmgd->mtx);

	sdata_info(sdata,
		   "deauthenticating from %pM by local choice (reason=%d)\n",
		   req->bssid, req->reason_code);

	if (ifmgd->auth_data) {
		drv_mgd_prepare_tx(sdata->local, sdata);
		ieee80211_send_deauth_disassoc(sdata, req->bssid,
					       IEEE80211_STYPE_DEAUTH,
					       req->reason_code, tx,
					       frame_buf);
		ieee80211_destroy_auth_data(sdata, false);
		mutex_unlock(&ifmgd->mtx);

		report_frame = true;
		goto out;
	}

	if (ifmgd->associated &&
	    ether_addr_equal(ifmgd->associated->bssid, req->bssid)) {
		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       req->reason_code, tx, frame_buf);
		report_frame = true;
	}
	mutex_unlock(&ifmgd->mtx);

 out:
	if (report_frame)
		__cfg80211_send_deauth(sdata->dev, frame_buf,
				       IEEE80211_DEAUTH_FRAME_LEN);

	return 0;
}