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
struct TYPE_3__ {scalar_t__ atimWindow; } ;
struct TYPE_4__ {int tickIbssSendBeacon; TYPE_1__ sta; int /*<<< orphan*/  dtim; int /*<<< orphan*/  beaconInterval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MODE_IBSS ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpEnableBeacon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfReWriteBeaconStartAddress(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    wd->tickIbssSendBeacon++;    // Increase 1 per 10ms .
    zmw_leave_critical_section(dev);

    if ( wd->tickIbssSendBeacon == 40 )
    {
//        DbgPrint("20070727");
        zfHpEnableBeacon(dev, ZM_MODE_IBSS, wd->beaconInterval, wd->dtim, (u8_t)wd->sta.atimWindow);
        zmw_enter_critical_section(dev);
        wd->tickIbssSendBeacon = 0;
        zmw_leave_critical_section(dev);
    }
}