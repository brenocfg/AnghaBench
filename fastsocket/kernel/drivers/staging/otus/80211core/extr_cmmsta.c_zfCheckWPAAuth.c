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
typedef  int u16_t ;
struct zsBssInfo {int* wpaIe; int* rsnIe; } ;
struct TYPE_3__ {scalar_t__ wepStatus; int authMode; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int ZM_AES ; 
#define  ZM_AUTH_MODE_WPA 131 
#define  ZM_AUTH_MODE_WPA2 130 
#define  ZM_AUTH_MODE_WPA2PSK 129 
#define  ZM_AUTH_MODE_WPAPSK 128 
 scalar_t__ ZM_ENCRYPTION_AES ; 
 scalar_t__ ZM_ENCRYPTION_TKIP ; 
 int ZM_TKIP ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfCheckWPAAuth(zdev_t* dev, struct zsBssInfo* pBssInfo)
{
    u8_t   ret=TRUE;
    u8_t   pmkCount;
    u8_t   i;
    u16_t   encAlgoType = 0;

    zmw_get_wlan_dev(dev);

    if ( wd->sta.wepStatus == ZM_ENCRYPTION_TKIP )
    {
        encAlgoType = ZM_TKIP;
    }
    else if ( wd->sta.wepStatus == ZM_ENCRYPTION_AES )
    {
        encAlgoType = ZM_AES;
    }

    switch(wd->sta.authMode)
    {
        case ZM_AUTH_MODE_WPA:
        case ZM_AUTH_MODE_WPAPSK:
            if ( pBssInfo->wpaIe[1] == 0 )
            {
                ret = FALSE;
                break;
            }

            pmkCount = pBssInfo->wpaIe[12];
            for(i=0; i < pmkCount; i++)
            {
                if ( pBssInfo->wpaIe[17 + 4*i] == encAlgoType )
                {
                    ret = TRUE;
                    goto done;
                }
            }

            ret = FALSE;
            break;

        case ZM_AUTH_MODE_WPA2:
        case ZM_AUTH_MODE_WPA2PSK:
            if ( pBssInfo->rsnIe[1] == 0 )
            {
                ret = FALSE;
                break;
            }

            pmkCount = pBssInfo->rsnIe[8];
            for(i=0; i < pmkCount; i++)
            {
                if ( pBssInfo->rsnIe[13 + 4*i] == encAlgoType )
                {
                    ret = TRUE;
                    goto done;
                }
            }

            ret = FALSE;
            break;
    }

done:
    return ret;
}