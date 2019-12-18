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
typedef  int u16_t ;
struct TYPE_5__ {int wpaSupport; scalar_t__ wpaLen; int /*<<< orphan*/  wpaIe; } ;
struct TYPE_4__ {int* wpaSupport; scalar_t__* wpaLen; int /*<<< orphan*/ * wpaIe; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; TYPE_1__ ap; } ;

/* Variables and functions */
 scalar_t__ ZM_MAX_WPAIE_SIZE ; 
 scalar_t__ ZM_MODE_AP ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int zfwGetVapId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetWpaIe(zdev_t* dev, u8_t* ie, u8_t Length)
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

        zm_assert(Length < ZM_MAX_WPAIE_SIZE);
        if (Length < ZM_MAX_WPAIE_SIZE)
        {
            wd->ap.wpaLen[vapId] = Length;
            zfMemoryCopy(wd->ap.wpaIe[vapId], ie, wd->ap.wpaLen[vapId]);
        }

    }
    else
    {
        wd->sta.wpaLen = Length;
        zfMemoryCopy(wd->sta.wpaIe, ie, wd->sta.wpaLen);
    }
    //zfiWlanSetWpaSupport(dev, 1);
    if (wd->wlanMode == ZM_MODE_AP) // AP Mode
    {
        wd->ap.wpaSupport[vapId] = 1;
    }
    else
    {
        wd->sta.wpaSupport = 1;
    }

}