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
struct net_device {struct lbs_private* ml_priv; } ;
struct TYPE_2__ {long channel; } ;
struct lbs_private {TYPE_1__ curbssparams; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {long m; int e; } ;
struct chan_freq_power {scalar_t__ freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,long) ; 
 struct chan_freq_power* lbs_find_cfp_by_band_and_channel (struct lbs_private*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int lbs_get_freq(struct net_device *dev, struct iw_request_info *info,
			 struct iw_freq *fwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;
	struct chan_freq_power *cfp;

	lbs_deb_enter(LBS_DEB_WEXT);

	cfp = lbs_find_cfp_by_band_and_channel(priv, 0,
					   priv->curbssparams.channel);

	if (!cfp) {
		if (priv->curbssparams.channel)
			lbs_deb_wext("invalid channel %d\n",
			       priv->curbssparams.channel);
		return -EINVAL;
	}

	fwrq->m = (long)cfp->freq * 100000;
	fwrq->e = 1;

	lbs_deb_wext("freq %u\n", fwrq->m);
	lbs_deb_leave(LBS_DEB_WEXT);
	return 0;
}