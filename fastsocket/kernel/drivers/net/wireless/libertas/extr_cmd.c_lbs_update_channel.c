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
struct TYPE_2__ {int channel; } ;
struct lbs_private {TYPE_1__ curbssparams; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int lbs_get_channel (struct lbs_private*) ; 

int lbs_update_channel(struct lbs_private *priv)
{
	int ret;

	/* the channel in f/w could be out of sync; get the current channel */
	lbs_deb_enter(LBS_DEB_ASSOC);

	ret = lbs_get_channel(priv);
	if (ret > 0) {
		priv->curbssparams.channel = ret;
		ret = 0;
	}
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}