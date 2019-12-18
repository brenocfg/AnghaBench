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
typedef  void* u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {void** bssid; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpSetBssid (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfUpdateBssid(zdev_t* dev, u8_t* bssid)
{

    zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();

    //zmw_enter_critical_section(dev);
    wd->sta.bssid[0] = bssid[0] + (((u16_t) bssid[1]) << 8);
    wd->sta.bssid[1] = bssid[2] + (((u16_t) bssid[3]) << 8);
    wd->sta.bssid[2] = bssid[4] + (((u16_t) bssid[5]) << 8);
    //zmw_leave_critical_section(dev);

    zfHpSetBssid(dev, bssid);

}