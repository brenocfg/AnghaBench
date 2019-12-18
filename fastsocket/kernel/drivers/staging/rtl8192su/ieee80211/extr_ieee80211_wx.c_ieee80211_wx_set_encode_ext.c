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
struct iw_point {int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int ext_flags; int alg; scalar_t__ key_len; int /*<<< orphan*/  rx_seq; int /*<<< orphan*/  key; } ;
struct ieee80211_security {int flags; int enabled; int active_key; scalar_t__* key_sizes; int /*<<< orphan*/  level; } ;
struct ieee80211_device {int tx_keyidx; scalar_t__ iw_mode; scalar_t__ (* reset_port ) (struct net_device*) ;scalar_t__ reset_on_keychange; struct net_device* dev; int /*<<< orphan*/  (* set_security ) (struct net_device*,struct ieee80211_security*) ;struct ieee80211_crypt_data** crypt; } ;
struct ieee80211_crypto_ops {scalar_t__ (* set_key ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* init ) (int) ;} ;
struct ieee80211_crypt_data {int /*<<< orphan*/ * priv; struct ieee80211_crypto_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_WX (char*,int /*<<< orphan*/ ,...) ; 
#define  IW_ENCODE_ALG_CCMP 130 
 int IW_ENCODE_ALG_NONE ; 
#define  IW_ENCODE_ALG_TKIP 129 
#define  IW_ENCODE_ALG_WEP 128 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 int IW_ENCODE_EXT_SET_TX_KEY ; 
 int IW_ENCODE_INDEX ; 
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
 struct ieee80211_crypto_ops* ieee80211_get_crypto_ops (char const*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_crypt_data*) ; 
 struct ieee80211_crypt_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/ * stub1 (int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,struct ieee80211_security*) ; 
 scalar_t__ stub4 (struct net_device*) ; 

int ieee80211_wx_set_encode_ext(struct ieee80211_device *ieee,
                               struct iw_request_info *info,
                               union iwreq_data *wrqu, char *extra)
{
	int ret = 0;
	struct net_device *dev = ieee->dev;
        struct iw_point *encoding = &wrqu->encoding;
        struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
        int i, idx;
        int group_key = 0;
        const char *alg;
        struct ieee80211_crypto_ops *ops;
        struct ieee80211_crypt_data **crypt;

        struct ieee80211_security sec = {
                .flags = 0,
        };
	//printk("======>encoding flag:%x,ext flag:%x, ext alg:%d\n", encoding->flags,ext->ext_flags, ext->alg);
        idx = encoding->flags & IW_ENCODE_INDEX;
        if (idx) {
                if (idx < 1 || idx > WEP_KEYS)
                        return -EINVAL;
                idx--;
        } else
                idx = ieee->tx_keyidx;

        if (ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) {

                crypt = &ieee->crypt[idx];

                group_key = 1;
        } else {
                /* some Cisco APs use idx>0 for unicast in dynamic WEP */
		//printk("not group key, flags:%x, ext->alg:%d\n", ext->ext_flags, ext->alg);
                if (idx != 0 && ext->alg != IW_ENCODE_ALG_WEP)
                        return -EINVAL;
                if (ieee->iw_mode == IW_MODE_INFRA)

                        crypt = &ieee->crypt[idx];

                else
                        return -EINVAL;
        }

	sec.flags |= SEC_ENABLED;

        if ((encoding->flags & IW_ENCODE_DISABLED) ||
            ext->alg == IW_ENCODE_ALG_NONE) {
                if (*crypt)
                        ieee80211_crypt_delayed_deinit(ieee, crypt);

                for (i = 0; i < WEP_KEYS; i++)

			if (ieee->crypt[i] != NULL)

                                break;

                if (i == WEP_KEYS) {
                        sec.enabled = 0;
                      //  sec.encrypt = 0;
                        sec.level = SEC_LEVEL_0;
                        sec.flags |= SEC_LEVEL;
                }
		//printk("disabled: flag:%x\n", encoding->flags);
                goto done;
        }

	sec.enabled = 1;
    //    sec.encrypt = 1;

        switch (ext->alg) {
        case IW_ENCODE_ALG_WEP:
                alg = "WEP";
                break;
        case IW_ENCODE_ALG_TKIP:
                alg = "TKIP";
                break;
        case IW_ENCODE_ALG_CCMP:
                alg = "CCMP";
                break;
        default:
                IEEE80211_DEBUG_WX("%s: unknown crypto alg %d\n",
                                   dev->name, ext->alg);
                ret = -EINVAL;
                goto done;
        }
	printk("alg name:%s\n",alg);

	 ops = ieee80211_get_crypto_ops(alg);
        if (ops == NULL)
                ops = ieee80211_get_crypto_ops(alg);
        if (ops == NULL) {
                IEEE80211_DEBUG_WX("%s: unknown crypto alg %d\n",
                                   dev->name, ext->alg);
		printk("========>unknown crypto alg %d\n", ext->alg);
                ret = -EINVAL;
                goto done;
        }

        if (*crypt == NULL || (*crypt)->ops != ops) {
                struct ieee80211_crypt_data *new_crypt;

                ieee80211_crypt_delayed_deinit(ieee, crypt);

                new_crypt = kzalloc(sizeof(*new_crypt), GFP_KERNEL);
                if (new_crypt == NULL) {
                        ret = -ENOMEM;
                        goto done;
                }
                new_crypt->ops = ops;
                if (new_crypt->ops)
                        new_crypt->priv = new_crypt->ops->init(idx);
                if (new_crypt->priv == NULL) {
                        kfree(new_crypt);
                        ret = -EINVAL;
                        goto done;
                }
                *crypt = new_crypt;

 	}

        if (ext->key_len > 0 && (*crypt)->ops->set_key &&
            (*crypt)->ops->set_key(ext->key, ext->key_len, ext->rx_seq,
                                   (*crypt)->priv) < 0) {
                IEEE80211_DEBUG_WX("%s: key setting failed\n", dev->name);
		printk("key setting failed\n");
                ret = -EINVAL;
                goto done;
        }
#if 1
 //skip_host_crypt:
	//printk("skip_host_crypt:ext_flags:%x\n", ext->ext_flags);
        if (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) {
                ieee->tx_keyidx = idx;
                sec.active_key = idx;
                sec.flags |= SEC_ACTIVE_KEY;
        }

        if (ext->alg != IW_ENCODE_ALG_NONE) {
                //memcpy(sec.keys[idx], ext->key, ext->key_len);
                sec.key_sizes[idx] = ext->key_len;
                sec.flags |= (1 << idx);
                if (ext->alg == IW_ENCODE_ALG_WEP) {
                        sec.flags |= SEC_LEVEL;
                        sec.level = SEC_LEVEL_1;
                } else if (ext->alg == IW_ENCODE_ALG_TKIP) {
                        sec.flags |= SEC_LEVEL;
                        sec.level = SEC_LEVEL_2;
                } else if (ext->alg == IW_ENCODE_ALG_CCMP) {
                        sec.flags |= SEC_LEVEL;
                        sec.level = SEC_LEVEL_3;
                }
                /* Don't set sec level for group keys. */
                if (group_key)
                        sec.flags &= ~SEC_LEVEL;
        }
#endif
done:
        if (ieee->set_security)
                ieee->set_security(ieee->dev, &sec);

	 if (ieee->reset_on_keychange &&
            ieee->iw_mode != IW_MODE_INFRA &&
            ieee->reset_port && ieee->reset_port(dev)) {
                IEEE80211_DEBUG_WX("%s: reset_port failed\n", dev->name);
                return -EINVAL;
        }

        return ret;
}