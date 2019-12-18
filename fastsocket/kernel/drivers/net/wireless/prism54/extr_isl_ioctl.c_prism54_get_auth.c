#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union oid_res_t {int /*<<< orphan*/  u; } ;
struct iw_param {int flags; int value; } ;
union iwreq_data {struct iw_param param; } ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mib_sem; int /*<<< orphan*/  wpa; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
#define  DOT11_AUTH_BOTH 140 
#define  DOT11_AUTH_NONE 139 
#define  DOT11_AUTH_OS 138 
#define  DOT11_AUTH_SK 137 
 int /*<<< orphan*/  DOT11_OID_AUTHENABLE ; 
 int /*<<< orphan*/  DOT11_OID_DOT1XENABLE ; 
 int /*<<< orphan*/  DOT11_OID_EXUNENCRYPTED ; 
 int /*<<< orphan*/  DOT11_OID_PRIVACYINVOKED ; 
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 136 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
#define  IW_AUTH_CIPHER_GROUP 135 
#define  IW_AUTH_CIPHER_PAIRWISE 134 
#define  IW_AUTH_DROP_UNENCRYPTED 133 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 132 
#define  IW_AUTH_PRIVACY_INVOKED 131 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 int IW_AUTH_WPA_VERSION_DISABLED ; 
 int IW_AUTH_WPA_VERSION_WPA ; 
 int IW_AUTH_WPA_VERSION_WPA2 ; 
 scalar_t__ PRV_STATE_INIT ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ islpci_get_state (TYPE_1__*) ; 
 int mgt_get_request (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism54_get_auth(struct net_device *ndev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct iw_param *param = &wrqu->param;
	u32 wpa = 0;
	int ret = 0;
	union oid_res_t r;

	if (islpci_get_state(priv) < PRV_STATE_INIT)
		return 0;

	/* first get the flags */
	down_write(&priv->mib_sem);
	wpa = priv->wpa;
	up_write(&priv->mib_sem);

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_CIPHER_PAIRWISE:
	case IW_AUTH_CIPHER_GROUP:
	case IW_AUTH_KEY_MGMT:
		/*
		 * wpa_supplicant will control these internally
		 */
		ret = -EOPNOTSUPP;
		break;

	case IW_AUTH_WPA_VERSION:
		switch (wpa) {
		case 1:
			param->value = IW_AUTH_WPA_VERSION_WPA;
			break;
		case 2:
			param->value = IW_AUTH_WPA_VERSION_WPA2;
			break;
		case 0:
		default:
			param->value = IW_AUTH_WPA_VERSION_DISABLED;
			break;
		}
		break;

	case IW_AUTH_DROP_UNENCRYPTED:
		ret = mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, NULL, &r);
		if (ret >= 0)
			param->value = r.u > 0 ? 1 : 0;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		ret = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, NULL, &r);
		if (ret >= 0) {
			switch (r.u) {
			case DOT11_AUTH_OS:
				param->value = IW_AUTH_ALG_OPEN_SYSTEM;
				break;
			case DOT11_AUTH_BOTH:
			case DOT11_AUTH_SK:
				param->value = IW_AUTH_ALG_SHARED_KEY;
			case DOT11_AUTH_NONE:
			default:
				param->value = 0;
				break;
			}
		}
		break;

	case IW_AUTH_WPA_ENABLED:
		param->value = wpa > 0 ? 1 : 0;
		break;

	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		ret = mgt_get_request(priv, DOT11_OID_DOT1XENABLE, 0, NULL, &r);
		if (ret >= 0)
			param->value = r.u > 0 ? 1 : 0;
		break;

	case IW_AUTH_PRIVACY_INVOKED:
		ret = mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, NULL, &r);
		if (ret >= 0)
			param->value = r.u > 0 ? 1 : 0;
		break;

	default:
		return -EOPNOTSUPP;
	}
	return ret;
}