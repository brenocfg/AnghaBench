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
typedef  scalar_t__ u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct TYPE_3__ {scalar_t__ keyId; } ;
struct TYPE_4__ {int checksumTest; int enableProtectionMode; int rxPacketDump; TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_1 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfTimerClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u32_t zfiDebugCmd(zdev_t* dev, u32_t cmd, u32_t value)
{
    u16_t event;
    u32_t tick;
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();


    zmw_enter_critical_section(dev);

    if ( cmd == 0 )
    {   /* schedule timer */
        event = (u16_t) ((value >> 16) & 0xffff);
        tick = value & 0xffff;
        zfTimerSchedule(dev, event, tick);
    }
    else if ( cmd == 1 )
    {   /* cancel timer */
        event = (u16_t) (value & 0xffff);
        zfTimerCancel(dev, event);
    }
    else if ( cmd == 2 )
    {   /* clear timer */
        zfTimerClear(dev);
    }
    else if ( cmd == 3 )
    {   /* test timer */
        zfTimerSchedule(dev, 1,  500);
        zfTimerSchedule(dev, 2, 1000);
        zfTimerSchedule(dev, 3, 1000);
        zfTimerSchedule(dev, 4, 1000);
        zfTimerSchedule(dev, 5, 1500);
        zfTimerSchedule(dev, 6, 2000);
        zfTimerSchedule(dev, 7, 2200);
        zfTimerSchedule(dev, 6, 2500);
        zfTimerSchedule(dev, 8, 2800);
    }
    else if ( cmd == 4)
    {
        zfTimerSchedule(dev, 1,  500);
        zfTimerSchedule(dev, 2, 1000);
        zfTimerSchedule(dev, 3, 1000);
        zfTimerSchedule(dev, 4, 1000);
        zfTimerSchedule(dev, 5, 1500);
        zfTimerSchedule(dev, 6, 2000);
        zfTimerSchedule(dev, 7, 2200);
        zfTimerSchedule(dev, 6, 2500);
        zfTimerSchedule(dev, 8, 2800);
        zfTimerCancel(dev, 1);
        zfTimerCancel(dev, 3);
        zfTimerCancel(dev, 6);
    }
    else if ( cmd == 5 )
    {
        wd->sta.keyId = (u8_t) value;
    }
	else if ( cmd == 6 )
	{
	    /* 0: normal    1: always set TCP/UDP checksum zero */
        wd->checksumTest = value;
	}
	else if ( cmd == 7 )
	{
        wd->enableProtectionMode = value;
   	    zm_msg1_mm(ZM_LV_1, "wd->enableProtectionMode=", wd->enableProtectionMode);
	}
	else if ( cmd == 8 )
	{
        /* rx packet content dump */
        if (value)
        {
            wd->rxPacketDump = 1;
        }
        else
        {
            wd->rxPacketDump = 0;
        }
	}


    zmw_leave_critical_section(dev);

    return 0;
}