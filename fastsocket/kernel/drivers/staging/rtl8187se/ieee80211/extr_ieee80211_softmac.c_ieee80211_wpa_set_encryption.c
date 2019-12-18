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
struct TYPE_3__ {char* alg; int idx; scalar_t__ err; int /*<<< orphan*/  key_len; scalar_t__ key; scalar_t__ set_tx; int /*<<< orphan*/  seq; } ;
struct TYPE_4__ {TYPE_1__ crypt; } ;
struct ieee_param {int* sta_addr; TYPE_2__ u; } ;
struct ieee80211_security {int flags; int enabled; size_t active_key; int /*<<< orphan*/  level; int /*<<< orphan*/ * key_sizes; int /*<<< orphan*/ * keys; } ;
struct ieee80211_device {size_t tx_keyidx; scalar_t__ iw_mode; int /*<<< orphan*/  dev; scalar_t__ (* reset_port ) (int /*<<< orphan*/ ) ;scalar_t__ reset_on_keychange; int /*<<< orphan*/  (* set_security ) (int /*<<< orphan*/ ,struct ieee80211_security*) ;scalar_t__ host_decrypt; scalar_t__ host_encrypt; struct ieee80211_crypt_data** crypt; } ;
struct ieee80211_crypto_ops {scalar_t__ (* set_key ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* init ) (size_t) ;} ;
struct ieee80211_crypt_data {int /*<<< orphan*/ * priv; struct ieee80211_crypto_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE_CRYPT_ALG_NAME_LEN ; 
 scalar_t__ IEEE_CRYPT_ERR_CARD_CONF_FAILED ; 
 scalar_t__ IEEE_CRYPT_ERR_CRYPT_INIT_FAILED ; 
 scalar_t__ IEEE_CRYPT_ERR_KEY_SET_FAILED ; 
 scalar_t__ IEEE_CRYPT_ERR_UNKNOWN_ALG ; 
 scalar_t__ IW_MODE_INFRA ; 
 int SEC_ACTIVE_KEY ; 
 int SEC_ENABLED ; 
 int SEC_LEVEL ; 
 int /*<<< orphan*/  SEC_LEVEL_0 ; 
 int /*<<< orphan*/  SEC_LEVEL_1 ; 
 int /*<<< orphan*/  SEC_LEVEL_2 ; 
 int /*<<< orphan*/  SEC_LEVEL_3 ; 
 int WEP_KEYS ; 
 int /*<<< orphan*/  ieee80211_crypt_delayed_deinit (struct ieee80211_device*,struct ieee80211_crypt_data**) ; 
 struct ieee80211_crypto_ops* ieee80211_get_crypto_ops (char*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_crypt_data*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_crypt_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/ * stub1 (size_t) ; 
 scalar_t__ stub2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct ieee80211_security*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_wpa_set_encryption(struct ieee80211_device *ieee,
				  struct ieee_param *param, int param_len)
{
	int ret = 0;

	struct ieee80211_crypto_ops *ops;
	struct ieee80211_crypt_data **crypt;

	struct ieee80211_security sec = {
		.flags = 0,
	};

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';

	if (param_len !=
	    (int) ((char *) param->u.crypt.key - (char *) param) +
	    param->u.crypt.key_len) {
		printk("Len mismatch %d, %d\n", param_len,
			       param->u.crypt.key_len);
		return -EINVAL;
	}
	if (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) {
		if (param->u.crypt.idx >= WEP_KEYS)
			return -EINVAL;
		crypt = &ieee->crypt[param->u.crypt.idx];
	} else {
		return -EINVAL;
	}

	if (strcmp(param->u.crypt.alg, "none") == 0) {
		if (crypt) {
			sec.enabled = 0;
			// FIXME FIXME
			//sec.encrypt = 0;
			sec.level = SEC_LEVEL_0;
			sec.flags |= SEC_ENABLED | SEC_LEVEL;
			ieee80211_crypt_delayed_deinit(ieee, crypt);
		}
		goto done;
	}
	sec.enabled = 1;
// FIXME FIXME
//	sec.encrypt = 1;
	sec.flags |= SEC_ENABLED;

	/* IPW HW cannot build TKIP MIC, host decryption still needed. */
	if (!(ieee->host_encrypt || ieee->host_decrypt) &&
	    strcmp(param->u.crypt.alg, "TKIP"))
		goto skip_host_crypt;

	ops = ieee80211_get_crypto_ops(param->u.crypt.alg);
	if (ops == NULL && strcmp(param->u.crypt.alg, "WEP") == 0)
		ops = ieee80211_get_crypto_ops(param->u.crypt.alg);
	else if (ops == NULL && strcmp(param->u.crypt.alg, "TKIP") == 0)
		ops = ieee80211_get_crypto_ops(param->u.crypt.alg);
	else if (ops == NULL && strcmp(param->u.crypt.alg, "CCMP") == 0)
		ops = ieee80211_get_crypto_ops(param->u.crypt.alg);
	if (ops == NULL) {
		printk("unknown crypto alg '%s'\n", param->u.crypt.alg);
		param->u.crypt.err = IEEE_CRYPT_ERR_UNKNOWN_ALG;
		ret = -EINVAL;
		goto done;
	}

	if (*crypt == NULL || (*crypt)->ops != ops) {
		struct ieee80211_crypt_data *new_crypt;

		ieee80211_crypt_delayed_deinit(ieee, crypt);

		new_crypt = (struct ieee80211_crypt_data *)
			kmalloc(sizeof(*new_crypt), GFP_KERNEL);
		if (new_crypt == NULL) {
			ret = -ENOMEM;
			goto done;
		}
		memset(new_crypt, 0, sizeof(struct ieee80211_crypt_data));
		new_crypt->ops = ops;
		if (new_crypt->ops)
			new_crypt->priv =
				new_crypt->ops->init(param->u.crypt.idx);

		if (new_crypt->priv == NULL) {
			kfree(new_crypt);
			param->u.crypt.err = IEEE_CRYPT_ERR_CRYPT_INIT_FAILED;
			ret = -EINVAL;
			goto done;
		}

		*crypt = new_crypt;
	}

	if (param->u.crypt.key_len > 0 && (*crypt)->ops->set_key &&
	    (*crypt)->ops->set_key(param->u.crypt.key,
				   param->u.crypt.key_len, param->u.crypt.seq,
				   (*crypt)->priv) < 0) {
		printk("key setting failed\n");
		param->u.crypt.err = IEEE_CRYPT_ERR_KEY_SET_FAILED;
		ret = -EINVAL;
		goto done;
	}

 skip_host_crypt:
	if (param->u.crypt.set_tx) {
		ieee->tx_keyidx = param->u.crypt.idx;
		sec.active_key = param->u.crypt.idx;
		sec.flags |= SEC_ACTIVE_KEY;
	} else
		sec.flags &= ~SEC_ACTIVE_KEY;

	if (param->u.crypt.alg != NULL) {
		memcpy(sec.keys[param->u.crypt.idx],
		       param->u.crypt.key,
		       param->u.crypt.key_len);
		sec.key_sizes[param->u.crypt.idx] = param->u.crypt.key_len;
		sec.flags |= (1 << param->u.crypt.idx);

		if (strcmp(param->u.crypt.alg, "WEP") == 0) {
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_1;
		} else if (strcmp(param->u.crypt.alg, "TKIP") == 0) {
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_2;
		} else if (strcmp(param->u.crypt.alg, "CCMP") == 0) {
			sec.flags |= SEC_LEVEL;
			sec.level = SEC_LEVEL_3;
		}
	}
 done:
	if (ieee->set_security)
		ieee->set_security(ieee->dev, &sec);

	/* Do not reset port if card is in Managed mode since resetting will
	 * generate new IEEE 802.11 authentication which may end up in looping
	 * with IEEE 802.1X.  If your hardware requires a reset after WEP
	 * configuration (for example... Prism2), implement the reset_port in
	 * the callbacks structures used to initialize the 802.11 stack. */
	if (ieee->reset_on_keychange &&
	    ieee->iw_mode != IW_MODE_INFRA &&
	    ieee->reset_port &&
	    ieee->reset_port(ieee->dev)) {
		printk("reset_port failed\n");
		param->u.crypt.err = IEEE_CRYPT_ERR_CARD_CONF_FAILED;
		return -EINVAL;
	}

	return ret;
}