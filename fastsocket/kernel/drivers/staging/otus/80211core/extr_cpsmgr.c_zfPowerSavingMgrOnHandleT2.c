#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_6__ {scalar_t__ tempWakeUp; int /*<<< orphan*/  lastTxMulticastFrm; int /*<<< orphan*/  lastTxBroadcastFrm; int /*<<< orphan*/  lastTxUnicastFrm; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_2__ psMgr; } ;
struct TYPE_5__ {int /*<<< orphan*/  txMulticastFrm; int /*<<< orphan*/  txBroadcastFrm; int /*<<< orphan*/  txUnicastFrm; } ;
struct TYPE_8__ {TYPE_3__ sta; TYPE_1__ commTally; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_PS_MSG_STATE_SLEEP ; 
 TYPE_4__* wd ; 
 scalar_t__ zfHpGetFreeTxdCount (int /*<<< orphan*/ *) ; 
 scalar_t__ zfHpGetMaxTxdCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpPowerSaveSetState (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfPowerSavingMgrOnHandleT2(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    // Wait until the Null pkt is transmitted
    if ( zfHpGetFreeTxdCount(dev) != zfHpGetMaxTxdCount(dev) )
    {
        return;
    }

    zmw_enter_critical_section(dev);
    wd->sta.psMgr.state = ZM_PS_MSG_STATE_SLEEP;
    wd->sta.psMgr.lastTxUnicastFrm = wd->commTally.txUnicastFrm;
    wd->sta.psMgr.lastTxBroadcastFrm = wd->commTally.txBroadcastFrm;
    wd->sta.psMgr.lastTxMulticastFrm = wd->commTally.txMulticastFrm;
    zmw_leave_critical_section(dev);

    // Let CHIP sleep now
zm_debug_msg0("zfPowerSavingMgrOnHandleT2 zzzz....\n");
    zfHpPowerSaveSetState(dev, 1);
    wd->sta.psMgr.tempWakeUp = 0;
}