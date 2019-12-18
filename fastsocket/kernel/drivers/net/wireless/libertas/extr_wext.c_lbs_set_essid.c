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
typedef  int u8 ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  radio_on; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; int /*<<< orphan*/  flags; } ;
struct assoc_request {int ssid_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  ssid; } ;
typedef  int /*<<< orphan*/  ssid ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_FLAG_SSID ; 
 int /*<<< orphan*/  DECLARE_SSID_BUF (int /*<<< orphan*/ ) ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_cancel_association_work (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,...) ; 
 struct assoc_request* lbs_get_association_request (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_postpone_association_work (struct lbs_private*) ; 
 int /*<<< orphan*/  memcpy (int**,...) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_ssid (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssid_buf ; 

__attribute__((used)) static int lbs_set_essid(struct net_device *dev, struct iw_request_info *info,
		   struct iw_point *dwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;
	int ret = 0;
	u8 ssid[IW_ESSID_MAX_SIZE];
	u8 ssid_len = 0;
	struct assoc_request * assoc_req;
	int in_ssid_len = dwrq->length;
	DECLARE_SSID_BUF(ssid_buf);

	lbs_deb_enter(LBS_DEB_WEXT);

	if (!priv->radio_on) {
		ret = -EINVAL;
		goto out;
	}

	/* Check the size of the string */
	if (in_ssid_len > IW_ESSID_MAX_SIZE) {
		ret = -E2BIG;
		goto out;
	}

	memset(&ssid, 0, sizeof(ssid));

	if (!dwrq->flags || !in_ssid_len) {
		/* "any" SSID requested; leave SSID blank */
	} else {
		/* Specific SSID requested */
		memcpy(&ssid, extra, in_ssid_len);
		ssid_len = in_ssid_len;
	}

	if (!ssid_len) {
		lbs_deb_wext("requested any SSID\n");
	} else {
		lbs_deb_wext("requested SSID '%s'\n",
		             print_ssid(ssid_buf, ssid, ssid_len));
	}

out:
	mutex_lock(&priv->lock);
	if (ret == 0) {
		/* Get or create the current association request */
		assoc_req = lbs_get_association_request(priv);
		if (!assoc_req) {
			ret = -ENOMEM;
		} else {
			/* Copy the SSID to the association request */
			memcpy(&assoc_req->ssid, &ssid, IW_ESSID_MAX_SIZE);
			assoc_req->ssid_len = ssid_len;
			set_bit(ASSOC_FLAG_SSID, &assoc_req->flags);
			lbs_postpone_association_work(priv);
		}
	}

	/* Cancel the association request if there was an error */
	if (ret != 0) {
		lbs_cancel_association_work(priv);
	}

	mutex_unlock(&priv->lock);

	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}