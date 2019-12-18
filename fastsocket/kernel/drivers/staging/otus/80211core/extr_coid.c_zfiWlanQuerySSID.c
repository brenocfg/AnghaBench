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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
struct TYPE_5__ {int /*<<< orphan*/  ssidLen; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ssidLen; int /*<<< orphan*/ * ssid; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; TYPE_1__ ap; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfwGetVapId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanQuerySSID(zdev_t* dev, u8_t* ssid, u8_t* pSsidLength)
{
    u16_t vapId = 0;
    zmw_get_wlan_dev(dev);

    if (wd->wlanMode == ZM_MODE_AP)
    {
        vapId = zfwGetVapId(dev);

        if (vapId == 0xffff)
        {
            *pSsidLength = wd->ap.ssidLen[0];
            zfMemoryCopy(ssid, wd->ap.ssid[0], wd->ap.ssidLen[0]);
        }
        else
        {
            *pSsidLength = wd->ap.ssidLen[vapId + 1];
            zfMemoryCopy(ssid, wd->ap.ssid[vapId + 1], wd->ap.ssidLen[vapId + 1]);
        }
    }
    else
    {
        *pSsidLength = wd->sta.ssidLen;
        zfMemoryCopy(ssid, wd->sta.ssid, wd->sta.ssidLen);
    }
}