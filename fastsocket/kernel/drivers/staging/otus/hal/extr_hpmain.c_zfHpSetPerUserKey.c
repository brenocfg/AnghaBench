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
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsHpPriv {scalar_t__ dot11Mode; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 int ZM_CENC ; 
 scalar_t__ ZM_HAL_80211_MODE_IBSS_WPA2PSK ; 
 int ZM_TKIP ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpSetKey (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfHpSetPerUserKey(zdev_t* dev, u8_t user, u8_t keyId, u8_t* mac, u8_t type, u32_t* key, u32_t* micKey)
{
#ifdef ZM_ENABLE_IBSS_WPA2PSK
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv = wd->hpPrivate;

    if ( hpPriv->dot11Mode == ZM_HAL_80211_MODE_IBSS_WPA2PSK )
    { /* If not wpa2psk , use traditional */
        if(keyId)
        {  /* Set Group Key */
            zfHpSetKey(dev, user, 1, type, (u16_t *)mac, key);
        }
        else if(keyId == 0)
        {  /* Set Pairwise Key */
            zfHpSetKey(dev, user, 0, type, (u16_t *)mac, key);
        }
    }
    else
    {
        zfHpSetKey(dev, user, keyId, type, (u16_t *)mac, key);
    }
#else
    zfHpSetKey(dev, user, keyId, type, (u16_t *)mac, key);
#endif

            if ((type == ZM_TKIP)
#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
    {
        zfHpSetKey(dev, user, keyId + 1, type, (u16_t *)mac, micKey);
    }
    return 0;
}