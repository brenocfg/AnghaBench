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
typedef  int u32_t ;
struct TYPE_3__ {int /*<<< orphan*/  uapsdQ; } ;
struct TYPE_4__ {scalar_t__ wlanMode; int tick; TYPE_1__ ap; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfApAgingSta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfQueueAge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfMmApTimeTick(zdev_t* dev)
{
    u32_t now;
    zmw_get_wlan_dev(dev);

    //zm_debug_msg1("wd->wlanMode : ", wd->wlanMode);
    if (wd->wlanMode == ZM_MODE_AP)
    {
        /* => every 1.28 seconds */
        /* AP : aging STA that does not active for wd->ap.staAgingTime    */
        now = wd->tick & 0x7f;
        if (now == 0x0)
        {
            zfApAgingSta(dev);
        }
        else if (now == 0x1f)
        {
            zfQueueAge(dev, wd->ap.uapsdQ, wd->tick, 10000);
        }
        /* AP : check (wd->ap.protectedObss) and (wd->ap.bStaAssociated)  */
        /*      to enable NonErp and Protection mode                      */
        else if (now == 0x3f)
        {
            //zfApProtctionMonitor(dev);
        }
    }
}