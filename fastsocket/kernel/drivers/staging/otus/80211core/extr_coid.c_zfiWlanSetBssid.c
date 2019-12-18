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
typedef  int u16_t ;
struct TYPE_3__ {int /*<<< orphan*/  bDesiredBssid; int /*<<< orphan*/ * desiredBssid; } ;
struct TYPE_4__ {TYPE_1__ ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanSetBssid(zdev_t* dev, u8_t* bssid)
{
    u16_t i;
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    for (i=0; i<6; i++)
    {
        wd->ws.desiredBssid[i] = bssid[i];
    }
    wd->ws.bDesiredBssid = TRUE;
    zmw_leave_critical_section(dev);

}