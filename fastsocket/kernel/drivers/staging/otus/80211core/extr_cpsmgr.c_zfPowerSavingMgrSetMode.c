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
typedef  int u16_t ;
struct TYPE_4__ {int maxSleepPeriods; int state; scalar_t__ tempWakeUp; } ;
struct TYPE_5__ {int powerSaveMode; TYPE_1__ psMgr; } ;
struct TYPE_6__ {scalar_t__ wlanMode; int /*<<< orphan*/  beaconInterval; TYPE_2__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int ZM_PS_MAX_SLEEP_PERIODS ; 
#define  ZM_PS_MSG_STATE_ACTIVE 133 
#define  ZM_PS_MSG_STATE_SLEEP 132 
 int ZM_PS_MSG_STATE_T1 ; 
#define  ZM_STA_PS_FAST 131 
#define  ZM_STA_PS_LIGHT 130 
#define  ZM_STA_PS_MAX 129 
#define  ZM_STA_PS_NONE 128 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfHpPowerSaveSetMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpPowerSaveSetState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfPowerSavingMgrHandlePs (int /*<<< orphan*/ *) ; 
 int zfPowerSavingMgrHandlePsNone (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfSendNullData (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfPowerSavingMgrSetMode(zdev_t* dev, u8_t mode)
{
    u16_t sendNull = 0;
    u8_t isWakeUpRequired = 0;

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zm_debug_msg1("mode = ", mode);

    if (mode > ZM_STA_PS_LIGHT)
    {
        zm_debug_msg0("return - wrong power save mode");
        return;
    }

    zmw_enter_critical_section(dev);

    #if 1
    switch(mode)
    {
        case ZM_STA_PS_NONE:
            sendNull = zfPowerSavingMgrHandlePsNone(dev, &isWakeUpRequired);
            break;

        case ZM_STA_PS_FAST:
        case ZM_STA_PS_LIGHT:
            wd->sta.psMgr.maxSleepPeriods = 1;
            zfPowerSavingMgrHandlePs(dev);
            break;

        case ZM_STA_PS_MAX:
            wd->sta.psMgr.maxSleepPeriods = ZM_PS_MAX_SLEEP_PERIODS;
            zfPowerSavingMgrHandlePs(dev);
            break;
    }
    #else
    switch(wd->sta.psMgr.state)
    {
        case ZM_PS_MSG_STATE_ACTIVE:
            if ( mode != ZM_STA_PS_NONE )
            {
zm_debug_msg0("zfPowerSavingMgrSetMode: switch from ZM_PS_MSG_STATE_ACTIVE to ZM_PS_MSG_STATE_T1\n");
                // Stall the TX & start to wait the pending TX to be completed
                wd->sta.psMgr.state = ZM_PS_MSG_STATE_T1;
            }
            break;

        case ZM_PS_MSG_STATE_SLEEP:
            break;
    }
    #endif

    wd->sta.powerSaveMode = mode;
    zmw_leave_critical_section(dev);

    if ( isWakeUpRequired )
    {
        zfHpPowerSaveSetState(dev, 0);
        wd->sta.psMgr.tempWakeUp = 0;
    }

    if ( zfStaIsConnected(dev)
         && (wd->wlanMode == ZM_MODE_INFRASTRUCTURE) )
    {
        switch(mode)
        {
            case ZM_STA_PS_NONE:
                zfHpPowerSaveSetMode(dev, 0, 0, wd->beaconInterval);
                break;

            case ZM_STA_PS_FAST:
            case ZM_STA_PS_MAX:
            case ZM_STA_PS_LIGHT:
                zfHpPowerSaveSetMode(dev, 0, 1, wd->beaconInterval);
                break;

            default:
                zfHpPowerSaveSetMode(dev, 0, 0, wd->beaconInterval);
                break;
        }
    }

    if (sendNull == 1)
    {
        zfSendNullData(dev, 0);
    }

    return;
}