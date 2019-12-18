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
typedef  int u8_t ;
typedef  int u32_t ;
struct TYPE_3__ {int currentFrequency; } ;
struct TYPE_4__ {int supportMode; TYPE_1__ sta; } ;

/* Variables and functions */
 int ZM_WIRELESS_MODE_24 ; 
 int ZM_WIRELESS_MODE_5 ; 
 TYPE_2__* wd ; 
 int zfChGetFirst2GhzChannel (int /*<<< orphan*/ *) ; 
 int zfChGetLast5GhzChannel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfiWlanQueryCurrentFrequency(zdev_t* dev, u8_t qmode)
{
    u32_t frequency;

    zmw_get_wlan_dev(dev);

    switch (qmode)
    {
    case 0:
        if (wd->sta.currentFrequency > 3000)
        {
            if (wd->supportMode & ZM_WIRELESS_MODE_5)
            {
                frequency = wd->sta.currentFrequency;
            }
            else if (wd->supportMode & ZM_WIRELESS_MODE_24)
            {
                frequency = zfChGetFirst2GhzChannel(dev);
            }
            else
            {
                frequency = 0;
            }
        }
        else
        {
            if (wd->supportMode & ZM_WIRELESS_MODE_24)
            {
                frequency = wd->sta.currentFrequency;
            }
            else if (wd->supportMode & ZM_WIRELESS_MODE_5)
            {
                frequency = zfChGetLast5GhzChannel(dev);
            }
            else
            {
                frequency = 0;
            }
        }
        break;

    case 1:
        frequency = wd->sta.currentFrequency;
        break;

    default:
        frequency = 0;
    }

    return (frequency*1000);
}