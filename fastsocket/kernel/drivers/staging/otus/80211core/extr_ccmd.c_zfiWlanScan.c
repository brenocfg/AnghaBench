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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u16_t ;
struct TYPE_4__ {int LEDCtrlFlagFromReg; int LEDCtrlFlag; } ;
struct TYPE_5__ {scalar_t__ scanFrequency; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_1__ ledStruct; TYPE_2__ sta; int /*<<< orphan*/  heartBeatNotification; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_BSSID_LIST_SCAN ; 
 int ZM_LED_CTRL_FLAG_ALPHA ; 
 scalar_t__ ZM_MODE_AP ; 
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_EXTERNAL ; 
 TYPE_3__* wd ; 
 int zfScanMgrScanStart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaBlockWlanScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfiWlanScan(zdev_t *dev)
{
	u16_t ret = 1;
	zmw_get_wlan_dev(dev);

	zm_debug_msg0("");

	zmw_declare_for_critical_section();

	zmw_enter_critical_section(dev);

	if (wd->wlanMode == ZM_MODE_AP) {
		wd->heartBeatNotification |= ZM_BSSID_LIST_SCAN;
		wd->sta.scanFrequency = 0;
		/* wd->sta.pUpdateBssList->bssCount = 0; */
		ret = 0;
	} else {
#if 0
		if (!zfStaBlockWlanScan(dev)) {
			zm_debug_msg0("scan request");
			/*zfTimerSchedule(dev, ZM_EVENT_SCAN, ZM_TICK_ZERO);*/
			ret = 0;
			goto start_scan;
		}
#else
		goto start_scan;
#endif
	}

	zmw_leave_critical_section(dev);

	return ret;

start_scan:
	zmw_leave_critical_section(dev);

	if (wd->ledStruct.LEDCtrlFlagFromReg & ZM_LED_CTRL_FLAG_ALPHA) {
		/* flag for Alpha */
		wd->ledStruct.LEDCtrlFlag |= ZM_LED_CTRL_FLAG_ALPHA;
	}

	ret = zfScanMgrScanStart(dev, ZM_SCAN_MGR_SCAN_EXTERNAL);

	zm_debug_msg1("ret = ", ret);

	return ret;
}