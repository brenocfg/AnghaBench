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
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_2__ {scalar_t__ wlanMode; int tick; int /*<<< orphan*/  swSniffer; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfAggScanAndClear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfPowerSavingMgrMain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaCheckConnectTimeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaCheckRxBeacon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaTimer100ms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerCheckAndHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfMmStaTimeTick(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    /* airopeek */
    if (wd->wlanMode != ZM_MODE_AP && !wd->swSniffer)
    {
        if ( wd->tick & 1 )
        {
            zfTimerCheckAndHandle(dev);
        }

        zfStaCheckRxBeacon(dev);
        zfStaTimer100ms(dev);
        zfStaCheckConnectTimeout(dev);
        zfPowerSavingMgrMain(dev);
    }

#ifdef ZM_ENABLE_AGGREGATION
    /*
     * add by honda
     */
    zfAggScanAndClear(dev, wd->tick);
#endif
}