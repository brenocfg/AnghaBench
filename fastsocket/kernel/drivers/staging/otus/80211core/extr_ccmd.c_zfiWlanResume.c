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
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {int /*<<< orphan*/  connectByReasso; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; int /*<<< orphan*/  macAddr; int /*<<< orphan*/  ExtOffset; int /*<<< orphan*/  BandWidth40; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfCoreSetFrequencyExV2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfFlushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpReinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpSetMacAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpSetRollCallTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpStartRecv (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnecting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfWlanEnable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfiWlanResume(zdev_t *dev, u8_t doReconn)
{
	u16_t ret;
	zmw_get_wlan_dev(dev);
	zmw_declare_for_critical_section();

	/* Redownload firmware, Reinit MAC,PHY,RF */
	zfHpReinit(dev, wd->frequency);

	/* Set channel according to AP's configuration */
	zfCoreSetFrequencyExV2(dev, wd->frequency, wd->BandWidth40,
		wd->ExtOffset, NULL, 1);

	zfHpSetMacAddress(dev, wd->macAddr, 0);

	/* Start Rx */
	zfHpStartRecv(dev);

	zfFlushVtxq(dev);

	if (wd->wlanMode != ZM_MODE_INFRASTRUCTURE &&
			wd->wlanMode != ZM_MODE_IBSS)
		return 1;

	zm_msg0_mm(ZM_LV_1, "Resume Wlan");
	if ((zfStaIsConnected(dev)) || (zfStaIsConnecting(dev))) {
		if (doReconn == 1) {
			zm_msg0_mm(ZM_LV_1, "Re-connect...");
			zmw_enter_critical_section(dev);
			wd->sta.connectByReasso = FALSE;
			zmw_leave_critical_section(dev);

			zfWlanEnable(dev);
		} else if (doReconn == 0)
			zfHpSetRollCallTable(dev);
	}

	ret = 0;

	return ret;
}