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
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; } ;
struct ieee80211_device {int tkip_countermeasures; int drop_unencrypted; int open_wep; int wpa_enabled; int ieee802_1x; int privacy_invoked; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 137 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
#define  IW_AUTH_CIPHER_GROUP 136 
#define  IW_AUTH_CIPHER_PAIRWISE 135 
#define  IW_AUTH_DROP_UNENCRYPTED 134 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 133 
#define  IW_AUTH_PRIVACY_INVOKED 132 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 131 
#define  IW_AUTH_TKIP_COUNTERMEASURES 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 

int ieee80211_wx_set_auth(struct ieee80211_device *ieee,
                               struct iw_request_info *info,
                               struct iw_param *data, char *extra)
{
/*
	 struct ieee80211_security sec = {
                .flags = SEC_AUTH_MODE,
	}
*/
	//printk("set auth:flag:%x, data value:%x\n", data->flags, data->value);
	switch (data->flags & IW_AUTH_INDEX) {
        case IW_AUTH_WPA_VERSION:
	     /*need to support wpa2 here*/
		//printk("wpa version:%x\n", data->value);
		break;
        case IW_AUTH_CIPHER_PAIRWISE:
        case IW_AUTH_CIPHER_GROUP:
        case IW_AUTH_KEY_MGMT:
                /*
 *                  * Host AP driver does not use these parameters and allows
 *                                   * wpa_supplicant to control them internally.
 *                                                    */
                break;
        case IW_AUTH_TKIP_COUNTERMEASURES:
                ieee->tkip_countermeasures = data->value;
                break;
        case IW_AUTH_DROP_UNENCRYPTED:
                ieee->drop_unencrypted = data->value;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		ieee->open_wep = (data->value&IW_AUTH_ALG_OPEN_SYSTEM)?1:0;
		//printk("open_wep:%d\n", ieee->open_wep);
		break;

#if 1
	case IW_AUTH_WPA_ENABLED:
		ieee->wpa_enabled = (data->value)?1:0;
		//printk("enalbe wpa:%d\n", ieee->wpa_enabled);
		break;

#endif
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
                ieee->ieee802_1x = data->value;
		break;
	case IW_AUTH_PRIVACY_INVOKED:
		ieee->privacy_invoked = data->value;
		break;
	default:
                return -EOPNOTSUPP;
	}
	return 0;
}