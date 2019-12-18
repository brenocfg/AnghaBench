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
struct hermes {int dummy; } ;
struct orinoco_private {scalar_t__ encode_alg; int firmware_type; int key_mgmt; int /*<<< orphan*/  iw_mode; scalar_t__ wep_restrict; int /*<<< orphan*/  has_wpa; scalar_t__ wpa_enabled; struct hermes hw; } ;

/* Variables and functions */
#define  FIRMWARE_TYPE_AGERE 130 
#define  FIRMWARE_TYPE_INTERSIL 129 
#define  FIRMWARE_TYPE_SYMBOL 128 
 int HERMES_AUTH_OPEN ; 
 int HERMES_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  HERMES_RID_CNFAUTHENTICATION ; 
 int /*<<< orphan*/  HERMES_RID_CNFAUTHENTICATION_AGERE ; 
 int /*<<< orphan*/  HERMES_RID_CNFSETWPAAUTHMGMTSUITE_AGERE ; 
 int /*<<< orphan*/  HERMES_RID_CNFWEPENABLED_AGERE ; 
 int /*<<< orphan*/  HERMES_RID_CNFWEPFLAGS_INTERSIL ; 
 int HERMES_WEP_EXCL_UNENCRYPTED ; 
 int HERMES_WEP_HOST_DECRYPT ; 
 int HERMES_WEP_PRIVACY_INVOKED ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 scalar_t__ ORINOCO_ALG_WEP ; 
 int /*<<< orphan*/  USER_BAP ; 
 int /*<<< orphan*/  __orinoco_hw_setup_wepkeys (struct orinoco_private*) ; 
 int hermes_write_wordrec (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int __orinoco_hw_setup_enc(struct orinoco_private *priv)
{
	struct hermes *hw = &priv->hw;
	int err = 0;
	int master_wep_flag;
	int auth_flag;
	int enc_flag;

	/* Setup WEP keys */
	if (priv->encode_alg == ORINOCO_ALG_WEP)
		__orinoco_hw_setup_wepkeys(priv);

	if (priv->wep_restrict)
		auth_flag = HERMES_AUTH_SHARED_KEY;
	else
		auth_flag = HERMES_AUTH_OPEN;

	if (priv->wpa_enabled)
		enc_flag = 2;
	else if (priv->encode_alg == ORINOCO_ALG_WEP)
		enc_flag = 1;
	else
		enc_flag = 0;

	switch (priv->firmware_type) {
	case FIRMWARE_TYPE_AGERE: /* Agere style WEP */
		if (priv->encode_alg == ORINOCO_ALG_WEP) {
			/* Enable the shared-key authentication. */
			err = hermes_write_wordrec(hw, USER_BAP,
					HERMES_RID_CNFAUTHENTICATION_AGERE,
					auth_flag);
		}
		err = hermes_write_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFWEPENABLED_AGERE,
					   enc_flag);
		if (err)
			return err;

		if (priv->has_wpa) {
			/* Set WPA key management */
			err = hermes_write_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFSETWPAAUTHMGMTSUITE_AGERE,
				  priv->key_mgmt);
			if (err)
				return err;
		}

		break;

	case FIRMWARE_TYPE_INTERSIL: /* Intersil style WEP */
	case FIRMWARE_TYPE_SYMBOL: /* Symbol style WEP */
		if (priv->encode_alg == ORINOCO_ALG_WEP) {
			if (priv->wep_restrict ||
			    (priv->firmware_type == FIRMWARE_TYPE_SYMBOL))
				master_wep_flag = HERMES_WEP_PRIVACY_INVOKED |
						  HERMES_WEP_EXCL_UNENCRYPTED;
			else
				master_wep_flag = HERMES_WEP_PRIVACY_INVOKED;

			err = hermes_write_wordrec(hw, USER_BAP,
						   HERMES_RID_CNFAUTHENTICATION,
						   auth_flag);
			if (err)
				return err;
		} else
			master_wep_flag = 0;

		if (priv->iw_mode == NL80211_IFTYPE_MONITOR)
			master_wep_flag |= HERMES_WEP_HOST_DECRYPT;

		/* Master WEP setting : on/off */
		err = hermes_write_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFWEPFLAGS_INTERSIL,
					   master_wep_flag);
		if (err)
			return err;

		break;
	}

	return 0;
}