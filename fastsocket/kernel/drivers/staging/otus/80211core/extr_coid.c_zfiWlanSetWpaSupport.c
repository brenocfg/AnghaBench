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
typedef  void* u8_t ;
typedef  int u16_t ;
struct TYPE_5__ {void* wpaSupport; } ;
struct TYPE_4__ {void** wpaSupport; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; TYPE_1__ ap; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 TYPE_3__* wd ; 
 int zfwGetVapId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetWpaSupport(zdev_t* dev, u8_t WpaSupport)
{
    u16_t vapId = 0;
    zmw_get_wlan_dev(dev);

    if (wd->wlanMode == ZM_MODE_AP) // AP Mode
    {
        vapId = zfwGetVapId(dev);

        if (vapId == 0xffff)
            vapId = 0;
        else
            vapId++;

        wd->ap.wpaSupport[vapId] = WpaSupport;
    }
    else
    {
        wd->sta.wpaSupport = WpaSupport;
    }

}