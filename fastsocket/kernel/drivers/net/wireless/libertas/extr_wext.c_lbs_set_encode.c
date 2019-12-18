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
typedef  int u16 ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int /*<<< orphan*/  lock; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; scalar_t__ length; } ;
struct TYPE_2__ {int /*<<< orphan*/  auth_mode; int /*<<< orphan*/  wep_enabled; } ;
struct assoc_request {int /*<<< orphan*/  flags; TYPE_1__ secinfo; int /*<<< orphan*/  wep_tx_keyidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_FLAG_SECINFO ; 
 int /*<<< orphan*/  ASSOC_FLAG_WEP_KEYS ; 
 int /*<<< orphan*/  ASSOC_FLAG_WEP_TX_KEYIDX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IW_AUTH_ALG_OPEN_SYSTEM ; 
 int /*<<< orphan*/  IW_AUTH_ALG_SHARED_KEY ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  disable_wep (struct assoc_request*) ; 
 int /*<<< orphan*/  disable_wpa (struct assoc_request*) ; 
 int /*<<< orphan*/  lbs_cancel_association_work (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 struct assoc_request* lbs_get_association_request (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_postpone_association_work (struct lbs_private*) ; 
 int lbs_set_wep_key (struct assoc_request*,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int validate_key_index (int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static int lbs_set_encode(struct net_device *dev,
		    struct iw_request_info *info,
		    struct iw_point *dwrq, char *extra)
{
	int ret = 0;
	struct lbs_private *priv = dev->ml_priv;
	struct assoc_request * assoc_req;
	u16 is_default = 0, index = 0, set_tx_key = 0;

	lbs_deb_enter(LBS_DEB_WEXT);

	mutex_lock(&priv->lock);
	assoc_req = lbs_get_association_request(priv);
	if (!assoc_req) {
		ret = -ENOMEM;
		goto out;
	}

	if (dwrq->flags & IW_ENCODE_DISABLED) {
		disable_wep (assoc_req);
		disable_wpa (assoc_req);
		goto out;
	}

	ret = validate_key_index(assoc_req->wep_tx_keyidx,
	                         (dwrq->flags & IW_ENCODE_INDEX),
	                         &index, &is_default);
	if (ret) {
		ret = -EINVAL;
		goto out;
	}

	/* If WEP isn't enabled, or if there is no key data but a valid
	 * index, set the TX key.
	 */
	if (!assoc_req->secinfo.wep_enabled || (dwrq->length == 0 && !is_default))
		set_tx_key = 1;

	ret = lbs_set_wep_key(assoc_req, extra, dwrq->length, index, set_tx_key);
	if (ret)
		goto out;

	if (dwrq->length)
		set_bit(ASSOC_FLAG_WEP_KEYS, &assoc_req->flags);
	if (set_tx_key)
		set_bit(ASSOC_FLAG_WEP_TX_KEYIDX, &assoc_req->flags);

	if (dwrq->flags & IW_ENCODE_RESTRICTED) {
		assoc_req->secinfo.auth_mode = IW_AUTH_ALG_SHARED_KEY;
	} else if (dwrq->flags & IW_ENCODE_OPEN) {
		assoc_req->secinfo.auth_mode = IW_AUTH_ALG_OPEN_SYSTEM;
	}

out:
	if (ret == 0) {
		set_bit(ASSOC_FLAG_SECINFO, &assoc_req->flags);
		lbs_postpone_association_work(priv);
	} else {
		lbs_cancel_association_work(priv);
	}
	mutex_unlock(&priv->lock);

	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}