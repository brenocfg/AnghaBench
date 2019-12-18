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
typedef  int u8_t ;
struct TYPE_4__ {scalar_t__ isSleepAllowed; scalar_t__ sleepAllowedtick; } ;
struct TYPE_5__ {scalar_t__ powerSaveMode; int ReceivedPktRatePerSecond; TYPE_1__ psMgr; scalar_t__ bChannelScan; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 scalar_t__ ZM_STA_PS_LIGHT ; 
 TYPE_3__* wd ; 
 scalar_t__ zfIsVtxqEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnecting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8_t zfPowerSavingMgrIsIdle(zdev_t *dev)
{
    u8_t isIdle = 0;

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    if ( zfStaIsConnected(dev) && wd->sta.psMgr.isSleepAllowed == 0 )
    {
        goto done;
    }

    if ( wd->sta.bChannelScan )
    {
        goto done;
    }

    if ( zfStaIsConnecting(dev) )
    {
        goto done;
    }

    if (wd->sta.powerSaveMode == ZM_STA_PS_LIGHT)
    {
        if (wd->sta.ReceivedPktRatePerSecond > 200)
        {
            goto done;
        }

        if ( zfStaIsConnected(dev)
             && (wd->wlanMode == ZM_MODE_INFRASTRUCTURE) )
        {
            if (wd->sta.psMgr.sleepAllowedtick) {
                wd->sta.psMgr.sleepAllowedtick--;
                goto done;
            }
        }
    }

    isIdle = 1;

done:
    zmw_leave_critical_section(dev);

    if ( zfIsVtxqEmpty(dev) == FALSE )
    {
        isIdle = 0;
    }

    return isIdle;
}