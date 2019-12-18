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
struct iw_param {long flags; int /*<<< orphan*/  value; } ;
union iwreq_data {struct iw_param param; } ;
struct net_device {int dummy; } ;
struct libipw_security {int /*<<< orphan*/  level; int /*<<< orphan*/  flags; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {size_t tx_keyidx; struct lib80211_crypt_data** crypt; } ;
struct libipw_device {int /*<<< orphan*/  privacy_invoked; int /*<<< orphan*/  ieee802_1x; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_security ) (int /*<<< orphan*/ ,struct libipw_security*) ;int /*<<< orphan*/  drop_unencrypted; TYPE_1__ crypt_info; } ;
struct lib80211_crypt_data {int /*<<< orphan*/  priv; TYPE_2__* ops; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {struct libipw_device* ieee; } ;
struct TYPE_4__ {unsigned long (* get_flags ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_flags ) (unsigned long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 unsigned long IEEE80211_CRYPTO_TKIP_COUNTERMEASURES ; 
#define  IW_AUTH_80211_AUTH_ALG 137 
#define  IW_AUTH_CIPHER_GROUP 136 
#define  IW_AUTH_CIPHER_PAIRWISE 135 
#define  IW_AUTH_DROP_UNENCRYPTED 134 
 long IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 133 
#define  IW_AUTH_PRIVACY_INVOKED 132 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 131 
#define  IW_AUTH_TKIP_COUNTERMEASURES 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 int /*<<< orphan*/  SEC_ENABLED ; 
 int /*<<< orphan*/  SEC_LEVEL ; 
 int /*<<< orphan*/  SEC_LEVEL_0 ; 
 int /*<<< orphan*/  SEC_LEVEL_1 ; 
 int ipw2100_wpa_enable (struct ipw2100_priv*,int /*<<< orphan*/ ) ; 
 int ipw2100_wpa_set_auth_algs (struct ipw2100_priv*,int /*<<< orphan*/ ) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 unsigned long stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct libipw_security*) ; 

__attribute__((used)) static int ipw2100_wx_set_auth(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	struct libipw_device *ieee = priv->ieee;
	struct iw_param *param = &wrqu->param;
	struct lib80211_crypt_data *crypt;
	unsigned long flags;
	int ret = 0;

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VERSION:
	case IW_AUTH_CIPHER_PAIRWISE:
	case IW_AUTH_CIPHER_GROUP:
	case IW_AUTH_KEY_MGMT:
		/*
		 * ipw2200 does not use these parameters
		 */
		break;

	case IW_AUTH_TKIP_COUNTERMEASURES:
		crypt = priv->ieee->crypt_info.crypt[priv->ieee->crypt_info.tx_keyidx];
		if (!crypt || !crypt->ops->set_flags || !crypt->ops->get_flags)
			break;

		flags = crypt->ops->get_flags(crypt->priv);

		if (param->value)
			flags |= IEEE80211_CRYPTO_TKIP_COUNTERMEASURES;
		else
			flags &= ~IEEE80211_CRYPTO_TKIP_COUNTERMEASURES;

		crypt->ops->set_flags(flags, crypt->priv);

		break;

	case IW_AUTH_DROP_UNENCRYPTED:{
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
			struct libipw_security sec = {
				.flags = SEC_ENABLED,
				.enabled = param->value,
			};
			priv->ieee->drop_unencrypted = param->value;
			/* We only change SEC_LEVEL for open mode. Others
			 * are set by ipw_wpa_set_encryption.
			 */
			if (!param->value) {
				sec.flags |= SEC_LEVEL;
				sec.level = SEC_LEVEL_0;
			} else {
				sec.flags |= SEC_LEVEL;
				sec.level = SEC_LEVEL_1;
			}
			if (priv->ieee->set_security)
				priv->ieee->set_security(priv->ieee->dev, &sec);
			break;
		}

	case IW_AUTH_80211_AUTH_ALG:
		ret = ipw2100_wpa_set_auth_algs(priv, param->value);
		break;

	case IW_AUTH_WPA_ENABLED:
		ret = ipw2100_wpa_enable(priv, param->value);
		break;

	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		ieee->ieee802_1x = param->value;
		break;

		//case IW_AUTH_ROAMING_CONTROL:
	case IW_AUTH_PRIVACY_INVOKED:
		ieee->privacy_invoked = param->value;
		break;

	default:
		return -EOPNOTSUPP;
	}
	return ret;
}