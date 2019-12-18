#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * wep_keys; scalar_t__* wep_keylens; } ;
typedef  TYPE_3__ wlandevice_t ;
struct iw_point {int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {TYPE_3__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int ext_flags; scalar_t__ alg; scalar_t__ key_len; int /*<<< orphan*/  key; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {int /*<<< orphan*/  msgcode; TYPE_1__ mibattribute; } ;
typedef  TYPE_4__ p80211msg_dot11req_mibset_t ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int /*<<< orphan*/  did; TYPE_2__ data; } ;
typedef  TYPE_5__ p80211item_pstr32_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DIDmib_dot11smt_dot11PrivacyTable_dot11WEPDefaultKeyID ; 
 int /*<<< orphan*/  DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey0 ; 
 int /*<<< orphan*/  DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey1 ; 
 int /*<<< orphan*/  DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey2 ; 
 int /*<<< orphan*/  DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey3 ; 
 int /*<<< orphan*/  DIDmsg_dot11req_mibset ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ IW_ENCODE_ALG_WEP ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 int IW_ENCODE_EXT_SET_TX_KEY ; 
 int IW_ENCODE_INDEX ; 
 int NUM_WEPKEYS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int p80211req_dorequest (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int p80211wext_dorequest (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int p80211wext_set_encodeext(struct net_device *dev,
				    struct iw_request_info *info,
				    union iwreq_data *wrqu, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
	p80211msg_dot11req_mibset_t msg;
	p80211item_pstr32_t *pstr;

	int result = 0;
	struct iw_point *encoding = &wrqu->encoding;
	int idx = encoding->flags & IW_ENCODE_INDEX;

	pr_debug("set_encode_ext flags[%d] alg[%d] keylen[%d]\n",
		 ext->ext_flags, (int)ext->alg, (int)ext->key_len);

	if (ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) {
		/* set default key ? I'm not sure if this the the correct thing to do here */

		if (idx) {
			if (idx < 1 || idx > NUM_WEPKEYS)
				return -EINVAL;
			else
				idx--;
		}
		pr_debug("setting default key (%d)\n", idx);
		result =
		    p80211wext_dorequest(wlandev,
					 DIDmib_dot11smt_dot11PrivacyTable_dot11WEPDefaultKeyID,
					 idx);
		if (result)
			return -EFAULT;
	}

	if (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) {
		if (ext->alg != IW_ENCODE_ALG_WEP) {
			pr_debug("asked to set a non wep key :(\n");
			return -EINVAL;
		}
		if (idx) {
			if (idx < 1 || idx > NUM_WEPKEYS)
				return -EINVAL;
			else
				idx--;
		}
		pr_debug("Set WEP key (%d)\n", idx);
		wlandev->wep_keylens[idx] = ext->key_len;
		memcpy(wlandev->wep_keys[idx], ext->key, ext->key_len);

		memset(&msg, 0, sizeof(msg));
		pstr = (p80211item_pstr32_t *) & msg.mibattribute.data;
		memcpy(pstr->data.data, ext->key, ext->key_len);
		pstr->data.len = ext->key_len;
		switch (idx) {
		case 0:
			pstr->did =
			    DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey0;
			break;
		case 1:
			pstr->did =
			    DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey1;
			break;
		case 2:
			pstr->did =
			    DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey2;
			break;
		case 3:
			pstr->did =
			    DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey3;
			break;
		default:
			break;
		}
		msg.msgcode = DIDmsg_dot11req_mibset;
		result = p80211req_dorequest(wlandev, (u8 *) & msg);
		pr_debug("result (%d)\n", result);
	}
	return result;
}