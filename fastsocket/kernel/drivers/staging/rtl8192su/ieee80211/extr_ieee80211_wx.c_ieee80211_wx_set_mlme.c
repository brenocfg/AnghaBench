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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct iw_request_info {int dummy; } ;
struct iw_mlme {int cmd; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IW_MLME_DEAUTH 129 
#define  IW_MLME_DISASSOC 128 
 int /*<<< orphan*/  ieee80211_disassociate (struct ieee80211_device*) ; 

int ieee80211_wx_set_mlme(struct ieee80211_device *ieee,
                               struct iw_request_info *info,
                               union iwreq_data *wrqu, char *extra)
{
	struct iw_mlme *mlme = (struct iw_mlme *) extra;

	switch (mlme->cmd) {
        case IW_MLME_DEAUTH:
	case IW_MLME_DISASSOC:
		ieee80211_disassociate(ieee);
		break;
	 default:
                return -EOPNOTSUPP;
        }

	return 0;
}