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
struct sockaddr {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {struct lbs_private* ml_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct lbs_private {scalar_t__ connect_status; TYPE_1__ curbssparams; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_get_wap(struct net_device *dev, struct iw_request_info *info,
			struct sockaddr *awrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (priv->connect_status == LBS_CONNECTED) {
		memcpy(awrq->sa_data, priv->curbssparams.bssid, ETH_ALEN);
	} else {
		memset(awrq->sa_data, 0, ETH_ALEN);
	}
	awrq->sa_family = ARPHRD_ETHER;

	lbs_deb_leave(LBS_DEB_WEXT);
	return 0;
}