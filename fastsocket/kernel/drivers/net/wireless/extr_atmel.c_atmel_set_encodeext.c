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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int alg; int ext_flags; scalar_t__ key_len; int /*<<< orphan*/  key; } ;
struct atmel_private {int default_key; int wep_is_on; int encryption_level; int* wep_key_len; int /*<<< orphan*/ * wep_keys; int /*<<< orphan*/  pairwise_cipher_suite; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPHER_SUITE_NONE ; 
 int /*<<< orphan*/  CIPHER_SUITE_WEP_128 ; 
 int /*<<< orphan*/  CIPHER_SUITE_WEP_64 ; 
 int EINPROGRESS ; 
 int EINVAL ; 
#define  IW_ENCODE_ALG_NONE 129 
#define  IW_ENCODE_ALG_WEP 128 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_EXT_SET_TX_KEY ; 
 int IW_ENCODE_INDEX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_set_encodeext(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu,
			    char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	struct iw_point *encoding = &wrqu->encoding;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
	int idx, key_len, alg = ext->alg, set_key = 1;

	/* Determine and validate the key index */
	idx = encoding->flags & IW_ENCODE_INDEX;
	if (idx) {
		if (idx < 1 || idx > 4)
			return -EINVAL;
		idx--;
	} else
		idx = priv->default_key;

	if (encoding->flags & IW_ENCODE_DISABLED)
	    alg = IW_ENCODE_ALG_NONE;

	if (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) {
		priv->default_key = idx;
		set_key = ext->key_len > 0 ? 1 : 0;
	}

	if (set_key) {
		/* Set the requested key first */
		switch (alg) {
		case IW_ENCODE_ALG_NONE:
			priv->wep_is_on = 0;
			priv->encryption_level = 0;
			priv->pairwise_cipher_suite = CIPHER_SUITE_NONE;
			break;
		case IW_ENCODE_ALG_WEP:
			if (ext->key_len > 5) {
				priv->wep_key_len[idx] = 13;
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_128;
				priv->encryption_level = 2;
			} else if (ext->key_len > 0) {
				priv->wep_key_len[idx] = 5;
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_64;
				priv->encryption_level = 1;
			} else {
				return -EINVAL;
			}
			priv->wep_is_on = 1;
			memset(priv->wep_keys[idx], 0, 13);
			key_len = min ((int)ext->key_len, priv->wep_key_len[idx]);
			memcpy(priv->wep_keys[idx], ext->key, key_len);
			break;
		default:
			return -EINVAL;
		}
	}

	return -EINPROGRESS;
}