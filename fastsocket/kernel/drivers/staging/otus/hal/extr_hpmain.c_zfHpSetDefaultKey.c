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
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsHpPriv {scalar_t__ dot11Mode; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 scalar_t__ ZM_CENC ; 
 scalar_t__ ZM_HAL_80211_MODE_IBSS_WPA2PSK ; 
 scalar_t__ ZM_TKIP ; 
 scalar_t__ ZM_USER_KEY_DEFAULT ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpSetKey (int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfHpSetDefaultKey(zdev_t* dev, u8_t keyId, u8_t type, u32_t* key, u32_t* micKey)
{
    u16_t macAddr[3] = {0, 0, 0};

    #ifdef ZM_ENABLE_IBSS_WPA2PSK
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv = wd->hpPrivate;

    if ( hpPriv->dot11Mode == ZM_HAL_80211_MODE_IBSS_WPA2PSK )
    { /* If not wpa2psk , use traditional */
      /* Because the bug of chip , defaultkey should follow the key map rule in register 700 */
        if ( keyId == 0 )
            zfHpSetKey(dev, ZM_USER_KEY_DEFAULT+keyId, 0, type, macAddr, key);
        else
            zfHpSetKey(dev, ZM_USER_KEY_DEFAULT+keyId, 1, type, macAddr, key);
    }
    else
        zfHpSetKey(dev, ZM_USER_KEY_DEFAULT+keyId, 0, type, macAddr, key);
    #else
        zfHpSetKey(dev, ZM_USER_KEY_DEFAULT+keyId, 0, type, macAddr, key);
    #endif
            if ((type == ZM_TKIP)

#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
    {
        zfHpSetKey(dev, ZM_USER_KEY_DEFAULT+keyId, 1, type, macAddr, micKey);
    }

    return 0;
}