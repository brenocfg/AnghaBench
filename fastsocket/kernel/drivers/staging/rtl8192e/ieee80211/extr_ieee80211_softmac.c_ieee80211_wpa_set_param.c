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
typedef  int u8 ;
typedef  void* u32 ;
struct ieee80211_security {void* enabled; int /*<<< orphan*/  level; int /*<<< orphan*/  flags; } ;
struct ieee80211_device {int wpax_type_set; int /*<<< orphan*/  wpax_suitlist_lock; void* wpax_type_notify; void* ieee802_1x; void* privacy_invoked; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_security ) (int /*<<< orphan*/ ,struct ieee80211_security*) ;void* drop_unencrypted; void* tkip_countermeasures; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IEEE_PARAM_AUTH_ALGS 134 
#define  IEEE_PARAM_DROP_UNENCRYPTED 133 
#define  IEEE_PARAM_IEEE_802_1X 132 
#define  IEEE_PARAM_PRIVACY_INVOKED 131 
#define  IEEE_PARAM_TKIP_COUNTERMEASURES 130 
#define  IEEE_PARAM_WPAX_SELECT 129 
#define  IEEE_PARAM_WPA_ENABLED 128 
 int /*<<< orphan*/  SEC_ENABLED ; 
 int /*<<< orphan*/  SEC_LEVEL ; 
 int /*<<< orphan*/  SEC_LEVEL_0 ; 
 int /*<<< orphan*/  SEC_LEVEL_1 ; 
 int ieee80211_wpa_enable (struct ieee80211_device*,void*) ; 
 int ieee80211_wpa_set_auth_algs (struct ieee80211_device*,void*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_security*) ; 

__attribute__((used)) static int ieee80211_wpa_set_param(struct ieee80211_device *ieee, u8 name, u32 value)
{
	int ret=0;
	unsigned long flags;

	switch (name) {
	case IEEE_PARAM_WPA_ENABLED:
		ret = ieee80211_wpa_enable(ieee, value);
		break;

	case IEEE_PARAM_TKIP_COUNTERMEASURES:
		ieee->tkip_countermeasures=value;
		break;

	case IEEE_PARAM_DROP_UNENCRYPTED: {
		/* HACK:
		 *
		 * wpa_supplicant calls set_wpa_enabled when the driver
		 * is loaded and unloaded, regardless of if WPA is being
		 * used.  No other calls are made which can be used to
		 * determine if encryption will be used or not prior to
		 * association being expected.  If encryption is not being
		 * used, drop_unencrypted is set to false, else true -- we
		 * can use this to determine if the CAP_PRIVACY_ON bit should
		 * be set.
		 */
		struct ieee80211_security sec = {
			.flags = SEC_ENABLED,
			.enabled = value,
		};
 		ieee->drop_unencrypted = value;
		/* We only change SEC_LEVEL for open mode. Others
		 * are set by ipw_wpa_set_encryption.
		 */
		if (!value) {
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_0;
		}
		else {
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_1;
		}
		if (ieee->set_security)
			ieee->set_security(ieee->dev, &sec);
		break;
	}

	case IEEE_PARAM_PRIVACY_INVOKED:
		ieee->privacy_invoked=value;
		break;

	case IEEE_PARAM_AUTH_ALGS:
		ret = ieee80211_wpa_set_auth_algs(ieee, value);
		break;

	case IEEE_PARAM_IEEE_802_1X:
		ieee->ieee802_1x=value;
		break;
	case IEEE_PARAM_WPAX_SELECT:
		// added for WPA2 mixed mode
		spin_lock_irqsave(&ieee->wpax_suitlist_lock,flags);
		ieee->wpax_type_set = 1;
		ieee->wpax_type_notify = value;
		spin_unlock_irqrestore(&ieee->wpax_suitlist_lock,flags);
		break;

	default:
		printk("Unknown WPA param: %d\n",name);
		ret = -EOPNOTSUPP;
	}

	return ret;
}