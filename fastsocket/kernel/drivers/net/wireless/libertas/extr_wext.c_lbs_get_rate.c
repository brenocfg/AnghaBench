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
struct lbs_private {scalar_t__ connect_status; int cur_rate; scalar_t__ enablehwauto; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; int fixed; } ;

/* Variables and functions */
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_get_rate(struct net_device *dev, struct iw_request_info *info,
		  struct iw_param *vwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (priv->connect_status == LBS_CONNECTED) {
		vwrq->value = priv->cur_rate * 500000;

		if (priv->enablehwauto)
			vwrq->fixed = 0;
		else
			vwrq->fixed = 1;

	} else {
		vwrq->fixed = 0;
		vwrq->value = 0;
	}

	lbs_deb_leave(LBS_DEB_WEXT);
	return 0;
}