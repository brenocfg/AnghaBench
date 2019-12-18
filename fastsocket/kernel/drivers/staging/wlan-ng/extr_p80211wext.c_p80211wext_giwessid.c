#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ ssid; } ;
typedef  TYPE_2__ wlandevice_t ;
struct iw_request_info {int dummy; } ;
struct iw_point {size_t length; int flags; } ;
struct TYPE_7__ {TYPE_2__* ml_priv; } ;
typedef  TYPE_3__ netdevice_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int p80211wext_giwessid(netdevice_t *dev,
			       struct iw_request_info *info,
			       struct iw_point *data, char *essid)
{
	wlandevice_t *wlandev = dev->ml_priv;

	if (wlandev->ssid.len) {
		data->length = wlandev->ssid.len;
		data->flags = 1;
		memcpy(essid, wlandev->ssid.data, data->length);
		essid[data->length] = 0;
	} else {
		memset(essid, 0, sizeof(wlandev->ssid.data));
		data->length = 0;
		data->flags = 0;
	}

	return 0;
}