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
struct TYPE_4__ {int /*<<< orphan*/  state; scalar_t__ sleepAllowedtick; } ;
struct TYPE_5__ {scalar_t__ powerSaveMode; int ReceivedPktRatePerSecond; TYPE_1__ psMgr; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_PS_MSG_STATE_T2 ; 
 scalar_t__ ZM_STA_PS_LIGHT ; 
 TYPE_3__* wd ; 
 scalar_t__ zfHpGetFreeTxdCount (int /*<<< orphan*/ *) ; 
 scalar_t__ zfHpGetMaxTxdCount (int /*<<< orphan*/ *) ; 
 scalar_t__ zfIsVtxqEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPowerSavingMgrNotifyPSToAP (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfPowerSavingMgrOnHandleT1(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    // If the tx Q is not empty...return
    if ( zfIsVtxqEmpty(dev) == FALSE )
    {
        return;
    }

zm_debug_msg0("VtxQ is empty now...Check if HAL TXQ is empty\n");

    // The the HAL TX Q is not empty...return
    if ( zfHpGetFreeTxdCount(dev) != zfHpGetMaxTxdCount(dev) )
    {
        return;
    }

zm_debug_msg0("HAL TXQ is empty now...Could go to sleep...\n");

    zmw_enter_critical_section(dev);

    if (wd->sta.powerSaveMode == ZM_STA_PS_LIGHT)
    {
        if (wd->sta.ReceivedPktRatePerSecond > 200)
        {
            zmw_leave_critical_section(dev);
            return;
        }

        if ( zfStaIsConnected(dev)
             && (wd->wlanMode == ZM_MODE_INFRASTRUCTURE) )
        {
            if (wd->sta.psMgr.sleepAllowedtick) {
                wd->sta.psMgr.sleepAllowedtick--;
                zmw_leave_critical_section(dev);
                return;
            }
        }
    }

    wd->sta.psMgr.state = ZM_PS_MSG_STATE_T2;

    zmw_leave_critical_section(dev);

    // Send the Null pkt to AP to notify that I'm going to sleep
    if ( zfStaIsConnected(dev) )
    {
zm_debug_msg0("zfPowerSavingMgrOnHandleT1 send Null data\n");
        zfPowerSavingMgrNotifyPSToAP(dev);
    }

    // Stall the TX now
    // zfTxEngineStop(dev);
}