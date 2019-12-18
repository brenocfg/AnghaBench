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
struct TYPE_4__ {int macmode; } ;
typedef  TYPE_1__ wlandevice_t ;
struct iw_request_info {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ml_priv; } ;
typedef  TYPE_2__ netdevice_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_AUTO ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  IW_MODE_MASTER ; 
#define  WLAN_MACMODE_ESS_AP 130 
#define  WLAN_MACMODE_ESS_STA 129 
#define  WLAN_MACMODE_IBSS_STA 128 

__attribute__((used)) static int p80211wext_giwmode(netdevice_t *dev,
			      struct iw_request_info *info,
			      __u32 *mode, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;

	switch (wlandev->macmode) {
	case WLAN_MACMODE_IBSS_STA:
		*mode = IW_MODE_ADHOC;
		break;
	case WLAN_MACMODE_ESS_STA:
		*mode = IW_MODE_INFRA;
		break;
	case WLAN_MACMODE_ESS_AP:
		*mode = IW_MODE_MASTER;
		break;
	default:
		/* Not set yet. */
		*mode = IW_MODE_AUTO;
	}

	return 0;
}