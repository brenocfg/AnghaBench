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
struct iw_point {int length; int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
struct libipw_security {scalar_t__* encode_alg; int /*<<< orphan*/ * keys; scalar_t__* key_sizes; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int tx_keyidx; } ;
struct libipw_device {scalar_t__ iw_mode; TYPE_1__ crypt_info; struct libipw_security sec; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int ext_flags; scalar_t__ alg; scalar_t__ key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IW_ENCODE_ALG_CCMP ; 
 scalar_t__ IW_ENCODE_ALG_NONE ; 
 scalar_t__ IW_ENCODE_ALG_TKIP ; 
 scalar_t__ IW_ENCODE_ALG_WEP ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 int IW_ENCODE_EXT_TX_SEQ_VALID ; 
 int IW_ENCODE_INDEX ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ SEC_ALG_CCMP ; 
 scalar_t__ SEC_ALG_TKIP ; 
 scalar_t__ SEC_ALG_WEP ; 
 int WEP_KEYS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct iw_encode_ext*,int /*<<< orphan*/ ,int) ; 

int libipw_wx_get_encodeext(struct libipw_device *ieee,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct iw_point *encoding = &wrqu->encoding;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
	struct libipw_security *sec = &ieee->sec;
	int idx, max_key_len;

	max_key_len = encoding->length - sizeof(*ext);
	if (max_key_len < 0)
		return -EINVAL;

	idx = encoding->flags & IW_ENCODE_INDEX;
	if (idx) {
		if (idx < 1 || idx > WEP_KEYS)
			return -EINVAL;
		idx--;
	} else
		idx = ieee->crypt_info.tx_keyidx;

	if (!(ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) &&
	    ext->alg != IW_ENCODE_ALG_WEP)
		if (idx != 0 || ieee->iw_mode != IW_MODE_INFRA)
			return -EINVAL;

	encoding->flags = idx + 1;
	memset(ext, 0, sizeof(*ext));

	if (!sec->enabled) {
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		encoding->flags |= IW_ENCODE_DISABLED;
	} else {
		if (sec->encode_alg[idx] == SEC_ALG_WEP)
			ext->alg = IW_ENCODE_ALG_WEP;
		else if (sec->encode_alg[idx] == SEC_ALG_TKIP)
			ext->alg = IW_ENCODE_ALG_TKIP;
		else if (sec->encode_alg[idx] == SEC_ALG_CCMP)
			ext->alg = IW_ENCODE_ALG_CCMP;
		else
			return -EINVAL;

		ext->key_len = sec->key_sizes[idx];
		memcpy(ext->key, sec->keys[idx], ext->key_len);
		encoding->flags |= IW_ENCODE_ENABLED;
		if (ext->key_len &&
		    (ext->alg == IW_ENCODE_ALG_TKIP ||
		     ext->alg == IW_ENCODE_ALG_CCMP))
			ext->ext_flags |= IW_ENCODE_EXT_TX_SEQ_VALID;

	}

	return 0;
}