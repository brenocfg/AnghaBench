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
struct TYPE_3__ {scalar_t__ bProtectionMode; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpSetSlotTime (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetProtectionMode(zdev_t* dev, u8_t mode)
{
    zmw_get_wlan_dev(dev);

    wd->sta.bProtectionMode = mode;
    if (wd->sta.bProtectionMode == TRUE)
    {
        zfHpSetSlotTime(dev, 0);
    }
    else
    {
        zfHpSetSlotTime(dev, 1);
    }

    zm_msg1_mm(ZM_LV_1, "wd->protectionMode=", wd->sta.bProtectionMode);
}