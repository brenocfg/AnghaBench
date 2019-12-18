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
struct TYPE_2__ {int hostwep; } ;
typedef  TYPE_1__ wlandevice_t ;
struct iw_param {int flags; int value; } ;
union iwreq_data {struct iw_param param; } ;
struct net_device {TYPE_1__* ml_priv; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int HOSTWEP_EXCLUDEUNENCRYPTED ; 
 int HOSTWEP_PRIVACYINVOKED ; 
 int HOSTWEP_SHAREDKEY ; 
#define  IW_AUTH_80211_AUTH_ALG 130 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
#define  IW_AUTH_DROP_UNENCRYPTED 129 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_PRIVACY_INVOKED 128 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int p80211_wext_get_iwauth(struct net_device *dev,
				  struct iw_request_info *info,
				  union iwreq_data *wrqu, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	struct iw_param *param = &wrqu->param;
	int result = 0;

	pr_debug("get_iwauth flags[%d]\n", (int)param->flags & IW_AUTH_INDEX);

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_DROP_UNENCRYPTED:
		param->value =
		    wlandev->hostwep & HOSTWEP_EXCLUDEUNENCRYPTED ? 1 : 0;
		break;

	case IW_AUTH_PRIVACY_INVOKED:
		param->value =
		    wlandev->hostwep & HOSTWEP_PRIVACYINVOKED ? 1 : 0;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		param->value =
		    wlandev->hostwep & HOSTWEP_SHAREDKEY ?
		    IW_AUTH_ALG_SHARED_KEY : IW_AUTH_ALG_OPEN_SYSTEM;
		break;

	default:
		break;
	}

	return result;
}