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
struct TYPE_4__ {int state; } ;
struct TYPE_5__ {TYPE_1__ psMgr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
#define  ZM_PS_MSG_STATE_ACTIVE 131 
#define  ZM_PS_MSG_STATE_SLEEP 130 
#define  ZM_PS_MSG_STATE_T1 129 
#define  ZM_PS_MSG_STATE_T2 128 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16_t zfPowerSavingMgrHandlePsNone(zdev_t* dev, u8_t *isWakeUpRequired)
{
    u16_t ret = 0;
    zmw_get_wlan_dev(dev);

    switch(wd->sta.psMgr.state)
    {
        case ZM_PS_MSG_STATE_ACTIVE:
            *isWakeUpRequired = 0;
            break;

        case ZM_PS_MSG_STATE_T1:
        case ZM_PS_MSG_STATE_T2:
        case ZM_PS_MSG_STATE_SLEEP:
        default:
            *isWakeUpRequired = 1;
zm_debug_msg0("zfPowerSavingMgrHandlePsNone: Wake up now\n");
            if ( zfStaIsConnected(dev) )
            {
                zm_debug_msg0("zfPowerSavingMgrOnHandleT1 send Null data\n");
                //zfSendNullData(dev, 0);
                ret = 1;
            }

            wd->sta.psMgr.state = ZM_PS_MSG_STATE_ACTIVE;
            break;
    }
    return ret;
}