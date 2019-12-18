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
struct iw_point {int flags; int length; } ;
union iwreq_data {struct iw_point encoding; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {scalar_t__ iw_mode; int tx_keyidx; scalar_t__ open_wep; struct ieee80211_crypt_data** crypt; } ;
struct ieee80211_crypt_data {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_key ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_WX (char*) ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int WEP_KEYS ; 
 int /*<<< orphan*/  WEP_KEY_LEN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ieee80211_wx_get_encode(struct ieee80211_device *ieee,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *keybuf)
{
	struct iw_point *erq = &(wrqu->encoding);
	int len, key;
	struct ieee80211_crypt_data *crypt;

	IEEE80211_DEBUG_WX("GET_ENCODE\n");

	if(ieee->iw_mode == IW_MODE_MONITOR)
		return -1;

	key = erq->flags & IW_ENCODE_INDEX;
	if (key) {
		if (key > WEP_KEYS)
			return -EINVAL;
		key--;
	} else
		key = ieee->tx_keyidx;

	crypt = ieee->crypt[key];
	erq->flags = key + 1;

	if (crypt == NULL || crypt->ops == NULL) {
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		return 0;
	}

	if (strcmp(crypt->ops->name, "WEP") != 0) {
		/* only WEP is supported with wireless extensions, so just
		 * report that encryption is used */
		erq->length = 0;
		erq->flags |= IW_ENCODE_ENABLED;
		return 0;
	}

	len = crypt->ops->get_key(keybuf, WEP_KEY_LEN, NULL, crypt->priv);
	erq->length = (len >= 0 ? len : 0);

	erq->flags |= IW_ENCODE_ENABLED;

	if (ieee->open_wep)
		erq->flags |= IW_ENCODE_OPEN;
	else
		erq->flags |= IW_ENCODE_RESTRICTED;

	return 0;
}