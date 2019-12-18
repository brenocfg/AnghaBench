#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wlandevice_t ;
struct iw_request_info {int dummy; } ;
struct iw_point {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ml_priv; } ;
typedef  TYPE_1__ netdevice_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int p80211wext_autojoin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlan_wext_write ; 

__attribute__((used)) static int p80211wext_siwcommit(netdevice_t *dev,
				struct iw_request_info *info,
				struct iw_point *data, char *essid)
{
	wlandevice_t *wlandev = dev->ml_priv;
	int err = 0;

	if (!wlan_wext_write) {
		err = (-EOPNOTSUPP);
		goto exit;
	}

	/* Auto Join */
	err = p80211wext_autojoin(wlandev);

exit:
	return err;
}