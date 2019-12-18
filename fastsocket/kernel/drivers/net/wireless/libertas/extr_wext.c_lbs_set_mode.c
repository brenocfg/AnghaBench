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
typedef  scalar_t__ u32 ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int /*<<< orphan*/  lock; } ;
struct iw_request_info {int dummy; } ;
struct assoc_request {int /*<<< orphan*/  flags; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_FLAG_MODE ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_AUTO ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_cancel_association_work (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,scalar_t__) ; 
 struct assoc_request* lbs_get_association_request (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_postpone_association_work (struct lbs_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_set_mode(struct net_device *dev,
		  struct iw_request_info *info, u32 * uwrq, char *extra)
{
	int ret = 0;
	struct lbs_private *priv = dev->ml_priv;
	struct assoc_request * assoc_req;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (   (*uwrq != IW_MODE_ADHOC)
	    && (*uwrq != IW_MODE_INFRA)
	    && (*uwrq != IW_MODE_AUTO)) {
		lbs_deb_wext("Invalid mode: 0x%x\n", *uwrq);
		ret = -EINVAL;
		goto out;
	}

	mutex_lock(&priv->lock);
	assoc_req = lbs_get_association_request(priv);
	if (!assoc_req) {
		ret = -ENOMEM;
		lbs_cancel_association_work(priv);
	} else {
		assoc_req->mode = *uwrq;
		set_bit(ASSOC_FLAG_MODE, &assoc_req->flags);
		lbs_postpone_association_work(priv);
		lbs_deb_wext("Switching to mode: 0x%x\n", *uwrq);
	}
	mutex_unlock(&priv->lock);

out:
	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}