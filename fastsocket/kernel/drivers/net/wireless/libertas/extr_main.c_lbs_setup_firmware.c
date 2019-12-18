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
struct lbs_private {void* txpower_max; void* txpower_min; void* txpower_cur; int /*<<< orphan*/  current_addr; } ;
typedef  void* s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LBS_DEB_FW ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int lbs_get_tx_power (struct lbs_private*,void**,void**,void**) ; 
 int /*<<< orphan*/  lbs_set_mac_control (struct lbs_private*) ; 
 int lbs_update_hw_spec (struct lbs_private*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_setup_firmware(struct lbs_private *priv)
{
	int ret = -1;
	s16 curlevel = 0, minlevel = 0, maxlevel = 0;

	lbs_deb_enter(LBS_DEB_FW);

	/* Read MAC address from firmware */
	memset(priv->current_addr, 0xff, ETH_ALEN);
	ret = lbs_update_hw_spec(priv);
	if (ret)
		goto done;

	/* Read power levels if available */
	ret = lbs_get_tx_power(priv, &curlevel, &minlevel, &maxlevel);
	if (ret == 0) {
		priv->txpower_cur = curlevel;
		priv->txpower_min = minlevel;
		priv->txpower_max = maxlevel;
	}

	lbs_set_mac_control(priv);
done:
	lbs_deb_leave_args(LBS_DEB_FW, "ret %d", ret);
	return ret;
}