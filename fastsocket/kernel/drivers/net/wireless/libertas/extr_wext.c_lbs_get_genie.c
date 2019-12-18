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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {scalar_t__ wpa_ie_len; int /*<<< orphan*/ * wpa_ie; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; } ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int lbs_get_genie(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_point *dwrq,
			  char *extra)
{
	int ret = 0;
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (priv->wpa_ie_len == 0) {
		dwrq->length = 0;
		goto out;
	}

	if (dwrq->length < priv->wpa_ie_len) {
		ret = -E2BIG;
		goto out;
	}

	dwrq->length = priv->wpa_ie_len;
	memcpy(extra, &priv->wpa_ie[0], priv->wpa_ie_len);

out:
	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}