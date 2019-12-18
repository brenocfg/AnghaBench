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
struct TYPE_2__ {int disabled; int /*<<< orphan*/  flags; } ;
union iwreq_data {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wl3501_card {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  pwr_state ;

/* Variables and functions */
 int /*<<< orphan*/  IW_POWER_ON ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_CURRENT_PWR_STATE ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int wl3501_get_mib_value (struct wl3501_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wl3501_get_power(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	u8 pwr_state;
	struct wl3501_card *this = netdev_priv(dev);
	int rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_CURRENT_PWR_STATE,
				      &pwr_state, sizeof(pwr_state));
	if (rc)
		goto out;
	wrqu->power.disabled = !pwr_state;
	wrqu->power.flags = IW_POWER_ON;
out:
	return rc;
}