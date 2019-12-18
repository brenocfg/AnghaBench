#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsTrafTally {int dummy; } ;
struct TYPE_3__ {int cmMicFailureCount; } ;
struct TYPE_4__ {int queueFlushed; TYPE_1__ sta; int /*<<< orphan*/  trafTally; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_EVENT_CM_TIMER ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfFlushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfGetWrapperSetting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpUsbReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfWlanEnable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfiWlanEnable(zdev_t *dev)
{
	u16_t ret;

	zmw_get_wlan_dev(dev);

	zm_msg0_mm(ZM_LV_1, "Enable Wlan");

	zfGetWrapperSetting(dev);

	zfZeroMemory((u8_t *) &wd->trafTally, sizeof(struct zsTrafTally));

	/* Reset cmMicFailureCount to 0 for new association request */
	if (wd->sta.cmMicFailureCount == 1) {
		zfTimerCancel(dev, ZM_EVENT_CM_TIMER);
		wd->sta.cmMicFailureCount = 0;
	}

	zfFlushVtxq(dev);
	if ((wd->queueFlushed & 0x10) != 0)
		zfHpUsbReset(dev);

	ret = zfWlanEnable(dev);

	return ret;
}