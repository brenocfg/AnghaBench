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
typedef  scalar_t__ u8_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int powerSaveMode; TYPE_1__ psMgr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_PS_MSG_STATE_T1 ; 
#define  ZM_STA_PS_FAST 131 
#define  ZM_STA_PS_LIGHT 130 
#define  ZM_STA_PS_MAX 129 
#define  ZM_STA_PS_NONE 128 
 TYPE_3__* wd ; 
 scalar_t__ zfPowerSavingMgrIsIdle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfPowerSavingMgrSleepIfIdle(zdev_t *dev)
{
    u8_t isIdle;

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    isIdle = zfPowerSavingMgrIsIdle(dev);

    if ( isIdle == 0 )
    {
        return;
    }

    zmw_enter_critical_section(dev);

    switch(wd->sta.powerSaveMode)
    {
        case ZM_STA_PS_NONE:
            break;

        case ZM_STA_PS_MAX:
        case ZM_STA_PS_FAST:
        case ZM_STA_PS_LIGHT:
            zm_debug_msg0("zfPowerSavingMgrSleepIfIdle: IDLE so slep now...\n");
            wd->sta.psMgr.state = ZM_PS_MSG_STATE_T1;
            break;
    }

    zmw_leave_critical_section(dev);
}