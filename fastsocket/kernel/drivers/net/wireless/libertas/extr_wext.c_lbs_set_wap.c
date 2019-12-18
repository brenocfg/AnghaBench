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
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  radio_on; } ;
struct iw_request_info {int dummy; } ;
struct assoc_request {int /*<<< orphan*/  flags; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  ASSOC_FLAG_BSSID ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_cancel_association_work (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,int /*<<< orphan*/ ) ; 
 struct assoc_request* lbs_get_association_request (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_postpone_association_work (struct lbs_private*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_set_wap(struct net_device *dev, struct iw_request_info *info,
		 struct sockaddr *awrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;
	struct assoc_request * assoc_req;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (!priv->radio_on)
		return -EINVAL;

	if (awrq->sa_family != ARPHRD_ETHER)
		return -EINVAL;

	lbs_deb_wext("ASSOC: WAP: sa_data %pM\n", awrq->sa_data);

	mutex_lock(&priv->lock);

	/* Get or create the current association request */
	assoc_req = lbs_get_association_request(priv);
	if (!assoc_req) {
		lbs_cancel_association_work(priv);
		ret = -ENOMEM;
	} else {
		/* Copy the BSSID to the association request */
		memcpy(&assoc_req->bssid, awrq->sa_data, ETH_ALEN);
		set_bit(ASSOC_FLAG_BSSID, &assoc_req->flags);
		lbs_postpone_association_work(priv);
	}

	mutex_unlock(&priv->lock);

	return ret;
}