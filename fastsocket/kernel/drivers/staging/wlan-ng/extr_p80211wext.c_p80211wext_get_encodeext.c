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
struct TYPE_2__ {int /*<<< orphan*/ * wep_keys; scalar_t__* wep_keylens; } ;
typedef  TYPE_1__ wlandevice_t ;
struct iw_point {int length; int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
struct net_device {TYPE_1__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {scalar_t__ key_len; int /*<<< orphan*/  key; scalar_t__ alg; int /*<<< orphan*/  ext_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IW_ENCODE_ALG_WEP ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_INDEX ; 
 int NUM_WEPKEYS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct iw_encode_ext*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 

__attribute__((used)) static int p80211wext_get_encodeext(struct net_device *dev,
				    struct iw_request_info *info,
				    union iwreq_data *wrqu, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;

	struct iw_point *encoding = &wrqu->encoding;
	int result = 0;
	int max_len;
	int idx;

	pr_debug("get_encode_ext flags[%d] alg[%d] keylen[%d]\n",
		 ext->ext_flags, (int)ext->alg, (int)ext->key_len);

	max_len = encoding->length - sizeof(*ext);
	if (max_len <= 0) {
		pr_debug("get_encodeext max_len [%d] invalid\n", max_len);
		result = -EINVAL;
		goto exit;
	}
	idx = encoding->flags & IW_ENCODE_INDEX;

	pr_debug("get_encode_ext index [%d]\n", idx);

	if (idx) {
		if (idx < 1 || idx > NUM_WEPKEYS) {
			pr_debug("get_encode_ext invalid key index [%d]\n",
				 idx);
			result = -EINVAL;
			goto exit;
		}
		idx--;
	} else {
		/* default key ? not sure what to do */
		/* will just use key[0] for now ! FIX ME */
	}

	encoding->flags = idx + 1;
	memset(ext, 0, sizeof(*ext));

	ext->alg = IW_ENCODE_ALG_WEP;
	ext->key_len = wlandev->wep_keylens[idx];
	memcpy(ext->key, wlandev->wep_keys[idx], ext->key_len);

	encoding->flags |= IW_ENCODE_ENABLED;
exit:
	return result;
}