#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
typedef  TYPE_1__ wlandevice_t ;
struct sockaddr {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ml_priv; } ;
typedef  TYPE_2__ netdevice_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  WLAN_BSSID_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p80211wext_giwap(netdevice_t *dev,
			    struct iw_request_info *info,
			    struct sockaddr *ap_addr, char *extra)
{

	wlandevice_t *wlandev = dev->ml_priv;

	memcpy(ap_addr->sa_data, wlandev->bssid, WLAN_BSSID_LEN);
	ap_addr->sa_family = ARPHRD_ETHER;

	return 0;
}