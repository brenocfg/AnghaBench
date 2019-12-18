#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int n_akm_suites; int /*<<< orphan*/ * akm_suites; } ;
struct TYPE_5__ {TYPE_1__ crypto; } ;
struct TYPE_6__ {TYPE_2__ connect; } ;
struct wireless_dev {TYPE_3__ wext; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_AUTH_KEY_MGMT_802_1X ; 
 int IW_AUTH_KEY_MGMT_PSK ; 
 int /*<<< orphan*/  WLAN_AKM_SUITE_8021X ; 
 int /*<<< orphan*/  WLAN_AKM_SUITE_PSK ; 

__attribute__((used)) static int cfg80211_set_key_mgt(struct wireless_dev *wdev, u32 key_mgt)
{
	int nr_akm_suites = 0;

	if (key_mgt & ~(IW_AUTH_KEY_MGMT_802_1X |
			IW_AUTH_KEY_MGMT_PSK))
		return -EINVAL;

	if (key_mgt & IW_AUTH_KEY_MGMT_802_1X) {
		wdev->wext.connect.crypto.akm_suites[nr_akm_suites] =
			WLAN_AKM_SUITE_8021X;
		nr_akm_suites++;
	}

	if (key_mgt & IW_AUTH_KEY_MGMT_PSK) {
		wdev->wext.connect.crypto.akm_suites[nr_akm_suites] =
			WLAN_AKM_SUITE_PSK;
		nr_akm_suites++;
	}

	wdev->wext.connect.crypto.n_akm_suites = nr_akm_suites;

	return 0;
}