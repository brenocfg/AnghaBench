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
struct TYPE_3__ {scalar_t__ flagKeyChanging; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfCoreSetKeyComplete(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

#if 0
    wd->sta.flagKeyChanging = 0;
#else
    if(wd->sta.flagKeyChanging)
    {
        zmw_enter_critical_section(dev);
        wd->sta.flagKeyChanging--;
        zmw_leave_critical_section(dev);
    }
#endif
    zm_debug_msg1("  zfCoreSetKeyComplete--- ", wd->sta.flagKeyChanging);

    zfPushVtxq(dev);
}