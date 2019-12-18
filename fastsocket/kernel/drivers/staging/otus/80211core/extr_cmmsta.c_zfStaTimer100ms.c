#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_2__ {int tick; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfStaTimer100ms(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    if ( (wd->tick % 10) == 0 )
    {
        zfPushVtxq(dev);
//        zfPowerSavingMgrMain(dev);
    }
}